/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:59:39 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/12 14:01:55 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "philo_one.h"

static bool	initialize_lock(t_config *config)
{
	return (pthread_mutex_init(&config->mutex_lock, NULL) == 0);
}

static t_config	*initialize_struct(int argc, char **argv)
{
	t_config	*config;

	config = malloc(sizeof(*config));
	if (!config)
		return (NULL);
	config->philosopher_count = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		config->eat_count = ft_atoi(argv[5]);
	else
		config->eat_count = -1;
	config->id = 0;
	/* config->is_eating = malloc(sizeof(int) * config->philosopher_count + 1); */
	/* if (!config->is_eating) */
	/* { */
	/* 	free(config); */
	/* 	return (NULL); */
	/* } */
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
	{
		free(*cfg);
		return (false);
	}
	*threads = malloc(sizeof(**threads) * (*cfg)->philosopher_count);
	if (!*threads)
	{
		free(*cfg);
		return (false);
	}
	gettimeofday(&(*cfg)->time_zero, NULL);
	return (true);
}
