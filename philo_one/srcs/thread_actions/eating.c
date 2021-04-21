/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 08:23:15 by ft                #+#    #+#             */
/*   Updated: 2021/04/19 15:13:12 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_forks(t_config *config, unsigned int id)
{
	unsigned int	left_fork;
	unsigned int	right_fork;

	left_fork = id;
	right_fork = id - 1;
	if (left_fork == config->philosopher_count)
		left_fork = 0;
	/* while ((config->is_eating[left_fork] || config->is_eating[right_fork]) */
	/* 		&& !config->is_over) */
		/* ; */
	pthread_mutex_lock(&config->main_mutex);
	pthread_mutex_lock(&config->forks[left_fork]);
	print_status(config, id, ACT_TAKE_FORK);
	pthread_mutex_lock(&config->forks[right_fork]);
	print_status(config, id, ACT_TAKE_FORK);
	/* config->is_eating[left_fork] = true; */
	/* config->is_eating[right_fork] = true; */
	/* printf("%d %d %d %d\n", config->is_eating[0], config->is_eating[1], config->is_eating[2], config->is_eating[3]); */
	pthread_mutex_unlock(&config->main_mutex);
}

void	drop_forks(t_config *config, unsigned int id)
{
	unsigned int	left_fork;
	unsigned int	right_fork;

	left_fork = id;
	right_fork = id - 1;
	if (left_fork == config->philosopher_count)
		left_fork = 0;
	/* printf("id:%d, left %d, right %d\n", id, left_fork, right_fork); */
	/* config->is_eating[left_fork] = false; */
	/* config->is_eating[right_fork] = false; */
	pthread_mutex_unlock(&config->forks[right_fork]);
	pthread_mutex_unlock(&config->forks[left_fork]);
}

