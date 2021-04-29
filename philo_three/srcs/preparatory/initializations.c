/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:59:39 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/29 23:28:55 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include "libft.h"
#include "philo_three.h"

static bool
	initialize_locks(t_config *config)
{
	config->sem = malloc(sizeof(*config->sem));
	if (!config->sem)
		return (false);
	sem_unlink(FORK_SEMAPHORE);
	config->sem->fork_semaphore = sem_open(FORK_SEMAPHORE, O_CREAT, 0644,
			config->philosopher_count);
	sem_unlink(MAIN_SEMAPHORE);
	config->sem->main_semaphore = sem_open(MAIN_SEMAPHORE, O_CREAT, 0644, 0);
	sem_unlink(OUTPUT_SEMAPHORE);
	config->sem->output_semaphore = sem_open(OUTPUT_SEMAPHORE, O_CREAT, 0644,
			1);
	sem_unlink(DEATH_SEMAPHORE);
	config->sem->death_semaphore = sem_open(DEATH_SEMAPHORE, O_CREAT, 0644, 0);
	sem_unlink(DONE_SEMAPHORE);
	config->sem->done_semaphore = sem_open(DONE_SEMAPHORE, O_CREAT, 0644, 0);
	if (!config->sem->fork_semaphore || !config->sem->main_semaphore
			|| !config->sem->output_semaphore || !config->sem->death_semaphore
			|| !config->sem->done_semaphore)
	{
		free_config(config);
		return (false);
	}
	return (true);
}

static t_config
	*initialize_struct(int argc, char **argv)
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
	config->pids = malloc(sizeof(*config->pids) * config->philosopher_count);
	if (!config->pids)
	{
		free(config);
		return (NULL);
	}
	config->is_over = false;
	return (config);
}

bool
	initialization(int argc, char **argv, t_config **config)
{
	if (!is_argcount_valid(argc))
		return (false);
	*config = initialize_struct(argc, argv);
	if (!is_input_valid(*config))
		return (false);
	if (!initialize_locks(*config))
		return (false);
	gettimeofday(&(*config)->time_zero, NULL);
	return (true);
}
