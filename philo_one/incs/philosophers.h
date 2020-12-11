/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:01:55 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/11 13:06:43 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>

# define ACT_EAT	1
# define ACT_SLEEP	2
# define ACT_THINK	3
# define ACT_DIE	4
# define ACT_DONE	5
# define CHECK_FREQ 5

typedef int	t_msec;
typedef struct timeval	t_tv;
typedef struct		s_philosopher
{
	unsigned int	philosopher_count;
	int				*is_eating;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	int				eat_count;
	int				id;
	pthread_mutex_t	mutex_lock;
	struct timeval	time_zero;
}					t_philosopher;

int					make_action(int action, int id, t_philosopher *philosopher);
int					get_timestamp(struct timeval time_zero);
int					can_eat(t_philosopher *philosopher, unsigned int id);
int					is_alive(t_tv time_of_death);

#endif
