/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:07 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/09 18:15:25 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include "philo_act.h"

static void	init_local_variables(t_config *config, t_local *local)
{
	local->time_of_death = add_ms(config->time_to_die);
	local->eat_count = config->eat_count;
	stop_execution(config->mutex_lock);
	(config->id)++;
	local->id = config->id;
	resume_execution(config->mutex_lock);
}

static bool	execute_actions(t_config *config, t_local *local)
{
	if (print_action(ACT_EAT, config, local))
		return (false);
	*t_death = add_ms(philo->time_to_die);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&philo->mutex_lock);
	philo->is_eating[id] = 0;
	pthread_mutex_unlock(&philo->mutex_lock);
	(*eat_count)--;
	if (!(*eat_count))
	{
		make_action(ACT_DONE, id, philo);
		return (0);
	}
	if (make_action(ACT_SLEEP, id, philo))
		return (0);
	usleep(get_time_to_wait(philo->time_to_sleep, *t_death));
	if (!is_alive(*t_death))
		return (1);
	if (make_action(ACT_THINK, id, philo))
		return (0);
	return (true);
}

void	*philo_act(t_config *config)
{
	t_local	local;

	init_local_variables(config, &local);
	printf("id: %d\n", local.id);
	while (is_alive(local.time_of_death))
	{
		stop_execution(config->mutex_lock);
		if (can_eat(config, local.id))
		{
			config->is_eating[local.id] = 1;
			resume_execution(config->mutex_lock);
			if (!execute_actions(config, &local))
				return (NULL);
		}
		resume_execution(config->mutex_lock);
	}
	return (NULL);
}
