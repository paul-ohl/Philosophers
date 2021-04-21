/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:59:39 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/21 19:49:01 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "philo_one.h"

static bool	initialize_lock(t_config *config)
{
	unsigned int	i;
	int				err;

	config->forks = malloc(sizeof(*config->forks) * config->philosopher_count);
	i = 0;
	err = pthread_mutex_init(&(config->main_mutex), NULL);
	while (i < config->philosopher_count)
	{
		err = pthread_mutex_init(&(config->forks[i]), NULL);
		if (err)
		{
			printf("Error with mutex initialization\n");
			while (i--)
				pthread_mutex_destroy(&(config->forks[i]));
			free(config->forks);
			config->forks = NULL;
			return (free_config(config, NULL));
		}
		i++;
	}
	return (true);
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
