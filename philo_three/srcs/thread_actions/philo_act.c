/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:07 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/29 11:55:00 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_three.h"
#include "philo_act.h"

static bool is_dead(struct timeval time_of_death)
{
	struct timeval  time_now;

	if (time_of_death.tv_sec == 0)
		return (false);
	gettimeofday(&time_now, NULL);
	if (time_now.tv_sec > time_of_death.tv_sec)
		return (true);
	else if (time_now.tv_sec < time_of_death.tv_sec)
		return (false);
	if (time_now.tv_usec > time_of_death.tv_usec)
		return (true);
	else
		return (false);
}

void	*check_death(void *config_v)
{
	t_config	*config;

	config = (t_config*)config_v;
	while (!config->is_over)
	{
		if (is_dead(config->time_of_death))
		{
			print_status(config, ACT_DIE);
			sem_post(config->sem->death_semaphore);
			config->is_over = true;
		}
	}
	return (NULL);
}

void	philo_eat(t_config *config)
{
	take_forks(config);
	print_status(config, ACT_EAT);
	config->time_of_death = add_ms(config->time_to_die);
	usleep(config->time_to_eat * 1000);
	(config->eat_count)--;
	drop_forks(config);
}

void	*philo_act(t_config *config)
{
	pthread_t	death_checker;

	config->time_of_death = add_ms(config->time_to_die);
	pthread_create(&death_checker, NULL, check_death, config);
	pthread_detach(death_checker);
	while (!config->is_over && config->eat_count != 0)
	{
		philo_eat(config);
		print_status(config, ACT_SLEEP);
		usleep(config->time_to_sleep * 1000);
		print_status(config, ACT_THINK);
		usleep(1000);
	}
	if (config->eat_count == 0)
	{
		print_status(config, ACT_DONE);
		sem_post(config->sem->done_semaphore);
	}
	return (NULL);
}
