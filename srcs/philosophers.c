/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:34:54 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/06 19:45:47 by paulohl          ###   ########.fr       */
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

	philosopher = (t_philosopher *)arg;
	gettimeofday(&time_of_death, NULL);
	add_ms(&time_of_death, philosopher->time_to_die);
	while (1)
	{
		while (is_alive(time_of_death) && philosopher->fork_count < 2)
			usleep(10000);
		if (!is_alive(time_of_death))
		{
			printf("Died\n");
			return (NULL);
		}
		philosopher->fork_count -= 2;
		printf("Eat for %dsecs\n", philosopher->time_to_eat);
		add_ms(&time_of_death, philosopher->time_to_die);
		usleep(philosopher->time_to_eat * 1000);
		philosopher->fork_count += 2;
		printf("Sleep for %dsecs\n", philosopher->time_to_sleep);
		usleep(philosopher->time_to_sleep * 1000);
		printf("Thinking now...\n");
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
	return (1);
}

int		main(int argc, char **argv)
{
	t_philosopher	philosopher;
	pthread_t		*thread;
	int				i;

	if (!valid_input(argc, argv, &philosopher))
		return (1);
	if (!(thread = malloc(sizeof(thread) * philosopher.philosopher_count)))
		return (1);
	i = -1;
	while (++i < philosopher.philosopher_count)
		pthread_create(&thread[i], NULL, start_philosophing, &philosopher);
	i = -1;
	while (++i < philosopher.philosopher_count)
		pthread_join(thread[i], NULL);
}
