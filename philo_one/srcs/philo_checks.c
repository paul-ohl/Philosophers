/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:04:02 by paulohl           #+#    #+#             */
/*   Updated: 2021/01/21 15:47:42 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		can_eat(t_conf *philosopher, unsigned int id)
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

int		is_alive(struct timeval time_of_death)
{
	struct timeval	current_time;

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

int	get_time_to_wait(t_msec time_to_check, struct timeval time_of_death)
{
	t_msec	tmp;
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
