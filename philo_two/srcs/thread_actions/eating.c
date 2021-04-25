/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 08:23:15 by ft                #+#    #+#             */
/*   Updated: 2021/04/25 15:44:56 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>

void	check_forks(t_config *config)
{
	sem_wait(config->main_semaphore);
	while (config->fork_count <= 1 && !config->is_over)
	{
		sem_post(config->main_semaphore);
		usleep(100);
		sem_wait(config->main_semaphore);
	}
}

void	take_forks(t_config *config, int id)
{
	check_forks(config);
	config->fork_count -= 2;
	sem_post(config->main_semaphore);
	sem_wait(config->fork_semaphore);
	print_status(config, id, ACT_TAKE_FORK);
	sem_wait(config->fork_semaphore);
	print_status(config, id, ACT_TAKE_FORK);
}

void	drop_forks(t_config *config)
{
	config->fork_count += 2;
	sem_post(config->fork_semaphore);
	sem_post(config->fork_semaphore);
}

