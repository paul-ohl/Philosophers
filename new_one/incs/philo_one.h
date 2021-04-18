/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:01:55 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/12 13:58:21 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>

# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

enum	e_actions
{
	ACT_ERROR = 0,
	ACT_EAT,
	ACT_SLEEP,
	ACT_THINK,
	ACT_DIE,
	ACT_DONE,
};

typedef int	t_msec;
typedef struct s_config
{
	unsigned int	philosopher_count;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	/* int				*is_eating; */
	int				eat_count;
	pthread_mutex_t	*forks;
	struct timeval	time_zero;
	bool			is_over;
	int				id;
}				t_config;

/* Output */
bool			print_error(const char *err);

/* Preparatory */
bool			is_input_valid(t_config *config);
bool			is_argcount_valid(int argc);
bool			initialization(int ac, char **av, t_config **c, pthread_t **t);

/* Thread actions */
void			stop_execution(pthread_mutex_t mutex_lock);
void			resume_execution(pthread_mutex_t mutex_lock);
void			start_threads(t_config *cfg, pthread_t *t, pthread_t *ctrl);
void			catch_threads(pthread_t *t, pthread_t ctrl, int philo_count);

/* Utils */
struct timeval	add_ms(t_msec ms);

#endif
