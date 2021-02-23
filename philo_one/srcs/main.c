/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:34:54 by paulohl           #+#    #+#             */
/*   Updated: 2021/02/10 09:58:43 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosophers.h"

int	get_timestamp(struct timeval time_zero)
{
	struct timeval	time_now;
	int		timestamp;

	gettimeofday(&time_now, NULL);
	timestamp = (time_now.tv_sec - time_zero.tv_sec) * 1000;
	timestamp += (time_now.tv_usec - time_zero.tv_usec) / 1000;
	return (timestamp);
}

struct timeval	add_ms(t_msec ms)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	timestamp.tv_sec += ms / 1000;
	ms = ms % 1000;
	timestamp.tv_usec += (ms * 1000);
	if (timestamp.tv_usec >= 1000000)
	{
		timestamp.tv_sec++;
		timestamp.tv_usec -= 1000000;
	}
	return (timestamp);
}

int	do_stuff(t_conf *philo, int id, struct timeval *t_death, int *eat_count)
{
	if (make_action(ACT_EAT, id, philo))
		return (0);
	*t_death = add_ms(philo->time_to_die);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&philo->mutex_lock);
	philo->is_eating[id] = 0;
	pthread_mutex_unlock(&philo->mutex_lock);
	(*eat_count)--;
	if (!(*eat_count))
	{
		make_action(ACT_DONE, id, philo);
		return (0);
	}
	if (make_action(ACT_SLEEP, id, philo))
		return (0);
	usleep(get_time_to_wait(philo->time_to_sleep, *t_death));
	if (!is_alive(*t_death))
		return (1);
	if (make_action(ACT_THINK, id, philo))
		return (0);
	return (1);
}

void	*start_philosophing(t_conf *philosopher)
{
	struct timeval	time_of_death;
	unsigned int	id;
	int				eat_count;

	time_of_death = add_ms(philosopher->time_to_die);
	eat_count = philosopher->eat_count;
	pthread_mutex_lock(&philosopher->mutex_lock);
	(philosopher->id)++;
	id = philosopher->id;
	pthread_mutex_unlock(&philosopher->mutex_lock);
	while (is_alive(time_of_death))
	{
		pthread_mutex_lock(&philosopher->mutex_lock);
		if (can_eat(philosopher, id))
		{
			philosopher->is_eating[id] = 1;
			pthread_mutex_unlock(&philosopher->mutex_lock);
			if (!do_stuff(philosopher, id, &time_of_death, &eat_count))
				return (NULL);
		}
		pthread_mutex_unlock(&philosopher->mutex_lock);
	}
	make_action(ACT_DIE, id, philosopher);
	pthread_mutex_lock(&philosopher->mutex_lock);
	philosopher->is_over = 1;
	pthread_mutex_unlock(&philosopher->mutex_lock);
	return (NULL);
}

int	valid_input(int argc, char **argv, t_conf *philo)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Wrong number of arguments\n", 26);
		if (argc == 1)
			write(2, "Usage: ./philo_one number_of_philosophers time_to_die "
					"time_to_eat time_to_sleep "
					"[number_of_time_each_philosophers_must_eat]\n", 124);
		return (0);
	}
	philo->philosopher_count = atoi(argv[1]);
	philo->time_to_die = atoi(argv[2]);
	philo->time_to_eat = atoi(argv[3]);
	philo->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		philo->eat_count = atoi(argv[5]);
	else
		philo->eat_count = -1;
	philo->id = 0;
	philo->is_over = 0;
	return (1);
}

int	main(int argc, char **argv)
{
	t_conf	philosopher;
	pthread_t		*thread;
	unsigned int	i;

	if (!valid_input(argc, argv, &philosopher))
		return (1);
	if (pthread_mutex_init(&philosopher.mutex_lock, NULL) != 0)
		return (2);
	if (!(thread = malloc(sizeof(thread) * philosopher.philosopher_count)))
		return (3);
	if (!(philosopher.is_eating =
				malloc(sizeof(int) * philosopher.philosopher_count)))
		return (4);
	i = -1;
	gettimeofday(&philosopher.time_zero, NULL);
	while (++i < philosopher.philosopher_count)
		pthread_create(&thread[i], NULL, (void*(*)(void*))start_philosophing, &philosopher);
	i = -1;
	while (++i < philosopher.philosopher_count)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&philosopher.mutex_lock);
	free(thread);
	free(philosopher.is_eating);
	return (0);
}
