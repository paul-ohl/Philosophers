/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:07 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/28 12:00:10 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_three.h"
#include "philo_act.h"

static void	init_variables(t_config *config, t_local *local)
{
	local->eat_count = config->eat_count;
	local->id = config->id;
	sem_wait(config->main_semaphore);
	printf("Hi! I'm %d\n", local->id);
	config->time_of_death[local->id] = add_ms(config->time_to_die);
	sem_post(config->main_semaphore);
}

void	philo_eat(t_config *config, t_local *local)
{
	if (!config->is_over)
	{
		take_forks(config, local->id);
		print_status(config, local->id, ACT_EAT);
		config->time_of_death[local->id] = add_ms(config->time_to_die);
		usleep(config->time_to_eat * 1000);
		(local->eat_count)--;
		drop_forks(config);
	}
}

void	philo_sleep(t_config *config, t_local *local)
{
	if (!config->is_over)
	{
		print_status(config, local->id, ACT_SLEEP);
		usleep(config->time_to_sleep * 1000);
	}
}

void	philo_think(t_config *config, t_local *local)
{
	print_status(config, local->id, ACT_THINK);
}

void	*philo_act(t_config *config)
{
	t_local	local;

	init_variables(config, &local);
	usleep(config->time_to_eat * (local.id % 2) / 2);
	while (!config->is_over && local.eat_count != 0)
	{
		philo_eat(config, &local);
		philo_sleep(config, &local);
		philo_think(config, &local);
		usleep(1000);
	}
	if (local.eat_count == 0)
	{
		print_status(config, local.id, ACT_DONE);
		config->time_of_death[local.id].tv_sec = 0;
		config->time_of_death[local.id].tv_usec = 0;
	}
	return (NULL);
}
