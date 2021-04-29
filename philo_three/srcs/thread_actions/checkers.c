/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 20:11:20 by ft                #+#    #+#             */
/*   Updated: 2021/04/29 22:48:08 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*wait_for_death_global(void *config_v)
{
	t_config	*config;

	config = (t_config *)config_v;
	sem_wait(config->sem->death_semaphore);
	sem_post(config->sem->main_semaphore);
	return (NULL);
}

void	*wait_for_done_eating_global(void *config_v)
{
	t_config	*config;
	int			i;

	config = (t_config *)config_v;
	i = 0;
	while (i < config->philosopher_count)
	{
		sem_wait(config->sem->done_semaphore);
		i++;
	}
	sem_post(config->sem->main_semaphore);
	return (NULL);
}
