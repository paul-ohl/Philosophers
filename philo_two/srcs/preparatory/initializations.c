/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:59:39 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/25 15:56:07 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include "libft.h"
#include "philo_two.h"

static bool	initialize_lock(t_config *config)
{
	sem_unlink(FORK_SEMAPHORE_NAME);
	config->fork_semaphore = sem_open(FORK_SEMAPHORE_NAME, O_CREAT, 0644,
			config->philosopher_count);
	if (config->fork_semaphore == NULL)
	{
		free_config(config, NULL);
		return (false);
	}
	sem_unlink(MAIN_SEMAPHORE_NAME);
	config->main_semaphore = sem_open(MAIN_SEMAPHORE_NAME, O_CREAT, 0644, 1);
	if (config->main_semaphore == NULL)
	{
		free_config(config, NULL);
		return (false);
	}
	return (true);
}

static t_config	*initialize_struct(int argc, char **argv)
{
	t_config	*config;

	config = malloc(sizeof(*config));
	if (!config)
		return (NULL);
	config = memset(config, 0, sizeof(*config));
	config->philosopher_count = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		config->eat_count = ft_atoi(argv[5]);
	else
		config->eat_count = -1;
	config->time_of_death = ft_calloc(sizeof(*config->time_of_death),
			config->philosopher_count + 1);
	if (!config->time_of_death)
	{
		free_config(config, NULL);
		return (NULL);
	}
	config->id = 0;
	config->is_over = false;
	return (config);
}

bool	initialization(int ac, char **av, t_config **cfg, pthread_t **threads)
{
	if (!is_argcount_valid(ac))
		return (false);
	*cfg = initialize_struct(ac, av);
	if (!is_input_valid(*cfg))
		return (false);
	if (!initialize_lock(*cfg))
		return (false);
	*threads = malloc(sizeof(**threads) * (*cfg)->philosopher_count);
	if (!*threads)
		return (free_config(*cfg, NULL));
	gettimeofday(&(*cfg)->time_zero, NULL);
	return (true);
}
