/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 18:11:45 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/18 19:47:07 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

struct timeval	add_ms(t_msec ms)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	timestamp.tv_sec += ms / 1000;
	ms = ms % 1000;
	timestamp.tv_usec += (ms * 1000);
	if (timestamp.tv_usec >= 1000000)
	{
		timestamp.tv_sec++;
		timestamp.tv_usec -= 1000000;
	}
	return (timestamp);
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
