/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:04:02 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/07 19:41:53 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

bool	can_eat(t_config *config, unsigned int id)
{
	unsigned int	previous;
	unsigned int	next;

	previous = id - 1;
	next = id + 1;
	if (id == 1)
		previous = config->philosopher_count;
	else if (id == config->philosopher_count)
		next = 1;
	if (!config->is_eating[previous] && !config->is_eating[next])
		return (true);
	return (false);
}

bool	is_alive(struct timeval time_of_death)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_sec > time_of_death.tv_sec)
		return (false);
	else if (current_time.tv_sec < time_of_death.tv_sec)
		return (true);
	else if (current_time.tv_usec > time_of_death.tv_usec)
		return (false);
	else
		return (true);
}

int	get_time_to_wait(t_msec time_to_check, struct timeval time_of_death)
{
	t_msec			tmp;
	struct timeval	current_time;
	struct timeval	death_svg;

	death_svg = time_of_death;
	tmp = time_to_check % 1000;
	if (time_of_death.tv_usec - (tmp * 1000) < 0)
	{
		time_of_death.tv_sec--;
		time_of_death.tv_usec = time_of_death.tv_usec - (tmp * 1000) + 1000000;
	}
	else
		time_of_death.tv_usec -= tmp * 1000;
	time_of_death.tv_sec -= time_to_check / 1000;
	if (is_alive(time_of_death))
		return (time_to_check * 1000);
	gettimeofday(&current_time, NULL);
	tmp = (death_svg.tv_sec - current_time.tv_sec) * 1000;
	tmp += (death_svg.tv_usec - current_time.tv_usec) / 1000;
	if (tmp < 0)
		tmp = 0;
	return (tmp * 1000);
}
