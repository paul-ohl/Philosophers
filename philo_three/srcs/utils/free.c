/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:17:50 by ft                #+#    #+#             */
/*   Updated: 2021/04/27 10:44:35 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdlib.h>

bool	free_config(t_config *config)
{
	if (config)
	{
		if (config->main_semaphore)
			sem_unlink(MAIN_SEMAPHORE_NAME);
		if (config->fork_semaphore)
			sem_unlink(FORK_SEMAPHORE_NAME);
		if (config->output_semaphore)
			sem_unlink(OUTPUT_SEMAPHORE_NAME);
		if (config->time_of_death)
			free(config->time_of_death);
		free(config);
	}
	return (false);
}
