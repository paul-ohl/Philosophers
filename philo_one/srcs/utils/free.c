/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:17:50 by ft                #+#    #+#             */
/*   Updated: 2021/04/25 16:13:02 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdlib.h>

bool	free_config(t_config *config, pthread_t *threads)
{
	int	i;

	if (config)
	{
		if (config->forks)
		{
			i = 0;
			while (i < config->philosopher_count)
				pthread_mutex_destroy(&(config->forks[i++]));
			free(config->forks);
		}
		if (config->time_of_death)
			free(config->time_of_death);
		free(config);
	}
	if (threads)
		free(threads);
	return (false);
}
