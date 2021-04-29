/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_act.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:38:27 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/29 23:09:58 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_one.h"

static bool
	is_dead(struct timeval time_of_death, int *finish_count)
{
	struct timeval	time_now;

	if (time_of_death.tv_sec == 0)
	{
		(*finish_count)++;
		return (false);
	}
	gettimeofday(&time_now, NULL);
	if (time_now.tv_sec > time_of_death.tv_sec)
		return (true);
	else if (time_now.tv_sec < time_of_death.tv_sec)
		return (false);
	if (time_now.tv_usec > time_of_death.tv_usec)
		return (true);
	else
		return (false);
}

void
	*controller_act(t_config *config)
{
	int	philosopher_id;
	int	finish_count;

	usleep(100);
	while (!config->is_over && finish_count < config->philosopher_count)
	{
		philosopher_id = 0;
		finish_count = 0;
		while (philosopher_id++ < config->philosopher_count)
		{
			if (is_dead(config->time_of_death[philosopher_id], &finish_count))
			{
				print_status(config, philosopher_id, ACT_DIE);
				config->is_over = true;
			}
		}
	}
	return (NULL);
}
