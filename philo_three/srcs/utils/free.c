/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:17:50 by ft                #+#    #+#             */
/*   Updated: 2021/04/29 22:38:53 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdlib.h>

bool	free_config(t_config *config)
{
	if (config)
	{
		if (config->sem)
		{
			if (config->sem->main_semaphore)
				sem_unlink(MAIN_SEMAPHORE);
			if (config->sem->fork_semaphore)
				sem_unlink(FORK_SEMAPHORE);
			if (config->sem->output_semaphore)
				sem_unlink(OUTPUT_SEMAPHORE);
			if (config->sem->death_semaphore)
				sem_unlink(DEATH_SEMAPHORE);
			if (config->sem->done_semaphore)
				sem_unlink(DONE_SEMAPHORE);
			free(config->sem);
		}
		if (config->pids)
			free(config->pids);
		free(config);
	}
	return (false);
}
