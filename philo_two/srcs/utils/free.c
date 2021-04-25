/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:17:50 by ft                #+#    #+#             */
/*   Updated: 2021/04/25 15:46:25 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdlib.h>

bool	free_config(t_config *config, pthread_t *threads)
{
	if (config)
	{
		if (config->main_semaphore)
			sem_unlink(MAIN_SEMAPHORE_NAME);
		if (config->fork_semaphore)
			sem_unlink(FORK_SEMAPHORE_NAME);
		if (config->time_of_death)
			free(config->time_of_death);
		free(config);
	}
	if (threads)
		free(threads);
	return (false);
}
