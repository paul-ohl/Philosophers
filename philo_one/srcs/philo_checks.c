/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:04:02 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/15 11:12:05 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		can_eat(t_philosopher *philosopher, unsigned int id)
{
	int		previous;
	int		next;

	previous = id - 1;
	next = id + 1;
	if (id == 1)
		previous = philosopher->philosopher_count;
	else if (id == philosopher->philosopher_count)
		next = 1;
	if (!philosopher->is_eating[previous] && !philosopher->is_eating[next])
		return (1);
	return (0);
}

int		is_alive(t_tv time_of_death)
{
	t_tv	current_time;

	if (gettimeofday(&current_time, NULL))
		return (-1);
	if (current_time.tv_sec > time_of_death.tv_sec)
		return (0);
	else if (current_time.tv_sec < time_of_death.tv_sec)
		return (1);
	else if (current_time.tv_usec > time_of_death.tv_usec)
		return (0);
	else
		return (1);
}
