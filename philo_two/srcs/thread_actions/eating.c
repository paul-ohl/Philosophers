/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 08:23:15 by ft                #+#    #+#             */
/*   Updated: 2021/04/25 15:55:58 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <unistd.h>

void	take_forks(t_config *config, int id)
{
	sem_post(config->main_semaphore);
	sem_wait(config->fork_semaphore);
	print_status(config, id, ACT_TAKE_FORK);
	sem_wait(config->fork_semaphore);
	print_status(config, id, ACT_TAKE_FORK);
}

void	drop_forks(t_config *config)
{
	sem_post(config->fork_semaphore);
	sem_post(config->fork_semaphore);
}

