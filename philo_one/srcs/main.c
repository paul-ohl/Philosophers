/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:34:54 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/11 13:14:08 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosophers.h"

int		get_timestamp(t_tv time_zero)
{
	t_tv	time_now;
	int		timestamp;

	gettimeofday(&time_now, NULL);
	timestamp = (time_now.tv_sec - time_zero.tv_sec) * 1000;
	timestamp += (time_now.tv_usec - time_zero.tv_usec) / 1000;
	return (timestamp);
}

void	add_ms(t_tv *timestamp, t_msec ms)
{
	gettimeofday(timestamp, NULL);
	timestamp->tv_sec += ms / 1000;
	ms = ms % 1000;
	timestamp->tv_usec += (ms * 1000);
	if (timestamp->tv_usec >= 1000000)
	{
		timestamp->tv_sec++;
		timestamp->tv_usec -= 1000000;
	}
}

int		do_stuff(t_philosopher *philo, int id, t_tv *t_death, int *eat_count)
{
	make_action(ACT_EAT, id, philo);
	add_ms(t_death, philo->time_to_die);
	usleep(philo->time_to_eat * 1000);
	philo->is_eating[id] = 0;
	(*eat_count)--;
	if (!(*eat_count))
		return (make_action(ACT_DONE, id, philo));
	make_action(ACT_SLEEP, id, philo);
	usleep(philo->time_to_sleep * 1000);
	make_action(ACT_THINK, id, philo);
	return (1);
}

void	*start_philosophing(void *arg)
{
	t_tv			time_of_death;
	t_philosopher	*philosopher;
	unsigned int	id;
	int				eat_count;

	philosopher = (t_philosopher *)arg;
	gettimeofday(&time_of_death, NULL);
	add_ms(&time_of_death, philosopher->time_to_die);
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
		else
			usleep(CHECK_FREQ * 1000);
		pthread_mutex_unlock(&philosopher->mutex_lock);
	}
	make_action(ACT_DIE, id, philosopher);
	return (NULL);
}

int		valid_input(int argc, char **argv, t_philosopher *philo)
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
	if (philo->time_to_die < philo->time_to_eat + philo->time_to_sleep)
	{
		write(2, "Your philosophers can't survive\ntime_to_die is lower"
				" than time_to_eat + time_to_sleep\n", 87);
		return (0);
	}
	philo->id = 0;
	return (1);
}

int		main(int argc, char **argv)
{
	t_philosopher	philosopher;
	pthread_t		*thread;
	unsigned int	i;

	if (!valid_input(argc, argv, &philosopher))
		return (1);
	if (pthread_mutex_init(&philosopher.mutex_lock, NULL) != 0)
		return (2);
	if (!(thread = malloc(sizeof(thread) * philosopher.philosopher_count)))
		return (3);
	if (!(philosopher.is_eating =
				malloc(sizeof(int) * philosopher.philosopher_count + 1)))
		return (4);
	i = -1;
	gettimeofday(&philosopher.time_zero, NULL);
	while (++i < philosopher.philosopher_count)
		pthread_create(&thread[i], NULL, start_philosophing, &philosopher);
	i = -1;
	while (++i < philosopher.philosopher_count)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&philosopher.mutex_lock);
	free(thread);
	free(philosopher.is_eating);
	return (0);
}