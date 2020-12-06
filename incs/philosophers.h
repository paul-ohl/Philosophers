/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:01:55 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/06 13:25:54 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>

typedef struct timeval	t_time;

typedef struct	s_philosopher
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	t_time		time_of_death;
}				t_philosopher;

#endif
