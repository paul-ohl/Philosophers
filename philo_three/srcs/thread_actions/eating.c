/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 08:23:15 by ft                #+#    #+#             */
/*   Updated: 2021/04/29 23:29:07 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>

void	take_forks(t_config *config)
{
	sem_wait(config->sem->fork_semaphore);
	print_status(config, ACT_TAKE_FORK);
	sem_wait(config->sem->fork_semaphore);
	print_status(config, ACT_TAKE_FORK);
}

void	drop_forks(t_config *config)
{
	sem_post(config->sem->fork_semaphore);
	sem_post(config->sem->fork_semaphore);
}
