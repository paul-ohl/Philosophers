/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:34:54 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/07 12:04:32 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosophers.h"

void	*my_turn(void *arg)
{
	int		*w;

	w = malloc(sizeof(int));
	for (int i = 0; i < 8; i++)
	{
		sleep(1);
		printf("%d: My turn!\n", i);
	}
	arg = 0;
	*w = 13;
	return (w);
}

int		is_alive(struct timeval time_of_death)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
		return (-1);
	if (current_time.tv_sec > time_of_death.tv_sec)
		return (0);
	else if (current_time.tv_sec < time_of_death.tv_sec)
		return (1);
	else if (current_time.tv_usec > time_of_death.tv_usec)
		return (0);
	else
		return (1);
}

void	add_ms(struct timeval *timestamp, t_msec ms)
{
	timestamp->tv_sec += ms / 1000;
	ms -= ms / 1000;
	timestamp->tv_usec += (ms * 1000);
	if (timestamp->tv_usec >= 1000000)
	{
		timestamp->tv_sec++;
		timestamp->tv_usec -= 1000000;
	}
}

void	*start_philosophing(void *arg)
{
	struct timeval	time_of_death;
	t_philosopher	*philosopher;
	int				id;

	philosopher = (t_philosopher *)arg;
	pthread_mutex_lock(&philosopher->mutex_lock);
	(philosopher->id)++;
	id = philosopher->id;
	pthread_mutex_unlock(&philosopher->mutex_lock);
	gettimeofday(&time_of_death, NULL);
	add_ms(&time_of_death, philosopher->time_to_die);
	while (1)
	{
		while (is_alive(time_of_death) && philosopher->fork_count < 2)
			usleep(10000);
		if (!is_alive(time_of_death))
		{
			printf("%d Died\n", id);
			return (NULL);
		}
		philosopher->fork_count -= 2;
		printf("%d Eat for %dsecs, fork_count: %d\n", id, philosopher->time_to_eat, philosopher->fork_count);
		add_ms(&time_of_death, philosopher->time_to_die);
		usleep(philosopher->time_to_eat * 1000);
		philosopher->fork_count += 2;
		printf("%d Sleep for %dsecs\n", id, philosopher->time_to_sleep);
		usleep(philosopher->time_to_sleep * 1000);
		printf("%d Thinking now...\n", id);
	}
	return (NULL);
}

int		valid_input(int argc, char **argv, t_philosopher *philo)
{
	if (argc < 5 || argc > 6)
		return (0);
	philo->philosopher_count = atoi(argv[1]);
	philo->fork_count = philo->philosopher_count;
	philo->time_to_die = atoi(argv[2]);
	philo->time_to_eat = atoi(argv[3]);
	philo->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		philo->eat_count = atoi(argv[5]);
	philo->id = 0;
	return (1);
}

int		main(int argc, char **argv)
{
	t_philosopher	philosopher;
	pthread_t		*thread;
	int				i;

	if (!valid_input(argc, argv, &philosopher))
		return (1);
	if (pthread_mutex_init(&philosopher.mutex_lock, NULL) != 0)
        return (2);
	if (!(thread = malloc(sizeof(thread) * philosopher.philosopher_count)))
		return (3);
	i = -1;
	while (++i < philosopher.philosopher_count)
		pthread_create(&thread[i], NULL, start_philosophing, &philosopher);
	i = -1;
	while (++i < philosopher.philosopher_count)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&philosopher.mutex_lock);
}
