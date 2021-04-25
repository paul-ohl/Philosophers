/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:04:02 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/22 12:44:08 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
