/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:04:02 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/15 11:12:39 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int             can_eat(t_philosopher *philosopher)
{
        if (philosopher->fork_count >= 2)
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
