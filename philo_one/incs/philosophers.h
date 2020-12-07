/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:01:55 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/07 13:09:14 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>

# define ACT_EAT	1
# define ACT_SLEEP	2
# define ACT_THINK	3
# define ACT_DIE	4
# define ACT_DONE	5

typedef int	t_msec;

typedef struct		s_philosopher
{
	int				philosopher_count;
	int				fork_count;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	int				eat_count;
	int				id;
	pthread_mutex_t	mutex_lock;
	struct timeval	time_zero;
}					t_philosopher;

#endif
