/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:01:55 by paulohl           #+#    #+#             */
/*   Updated: 2021/01/21 15:56:57 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# define ACT_EAT	1
# define ACT_SLEEP	2
# define ACT_THINK	3
# define ACT_DIE	4
# define ACT_DONE	5
# define CHECK_FREQ 5

typedef int			t_msec;
typedef struct s_conf
{
	unsigned int	philosopher_count;
	int				fork_count;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	int				eat_count;
	int				id;
	sem_t			*semaphore;
	struct timeval	time_zero;
	int				is_over;
}					t_conf;

int	make_action(int action, int id, t_conf *philosopher);
int	get_timestamp(struct timeval time_zero);
int	can_eat(t_conf *philosopher);
int	is_alive(struct timeval time_of_death);
int	get_time_to_wait(t_msec time_to_check, struct timeval time_of_death);

#endif