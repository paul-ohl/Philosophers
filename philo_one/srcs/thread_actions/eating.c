/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 08:23:15 by ft                #+#    #+#             */
/*   Updated: 2021/04/22 11:24:37 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <unistd.h>

void	check_forks(t_config *config, int left_fork, int right_fork)
{
	pthread_mutex_lock(&config->main_mutex);
	while ((config->is_eating[left_fork] || config->is_eating[right_fork])
			&& !config->is_over)
	{
		pthread_mutex_unlock(&config->main_mutex);
		usleep(100);
		pthread_mutex_lock(&config->main_mutex);
	}
}

void	take_forks(t_config *config, int id)
{
	int	left_fork;
	int	right_fork;

	left_fork = id;
	right_fork = id - 1;
	if (left_fork == config->philosopher_count)
		left_fork = 0;
	check_forks(config, left_fork, right_fork);
	pthread_mutex_lock(&config->forks[left_fork]);
	print_status(config, id, ACT_TAKE_FORK);
	pthread_mutex_lock(&config->forks[right_fork]);
	print_status(config, id, ACT_TAKE_FORK);
	config->is_eating[left_fork] = true;
	config->is_eating[right_fork] = true;
	pthread_mutex_unlock(&config->main_mutex);
}

void	drop_forks(t_config *config, int id)
{
	int	left_fork;
	int	right_fork;

	left_fork = id;
	right_fork = id - 1;
	if (left_fork == config->philosopher_count)
		left_fork = 0;
	config->is_eating[left_fork] = false;
	config->is_eating[right_fork] = false;
	pthread_mutex_unlock(&config->forks[right_fork]);
	pthread_mutex_unlock(&config->forks[left_fork]);
}

