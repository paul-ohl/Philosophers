/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:01:55 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/28 11:39:33 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

#include <stdio.h>

# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>

# define MAIN_SEMAPHORE_NAME "main_semaphore"
# define FORK_SEMAPHORE_NAME "fork_semaphore"
# define OUTPUT_SEMAPHORE_NAME "output_semaphore"

enum	e_actions
{
	ACT_ERROR = 0,
	ACT_TAKE_FORK,
	ACT_EAT,
	ACT_SLEEP,
	ACT_THINK,
	ACT_DIE,
	ACT_DONE,
};

typedef int	t_msec;
typedef struct s_config
{
	int				philosopher_count;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	int				eat_count;
	struct timeval	time_zero;
	struct timeval	*time_of_death;
	sem_t			*fork_semaphore;
	sem_t			*main_semaphore;
	sem_t			*output_semaphore;
	pid_t			*pids;
	int				id;
	bool			is_over;
}				t_config;

/* Output */
bool			print_error(const char *err);
void			print_status(t_config *config, int id, const int act);

/* Preparatory */
bool			is_input_valid(t_config *config);
bool			is_argcount_valid(int argc);
bool			initialization(int ac, char **av, t_config **c);

/* Thread actions */
void			stop_execution(pthread_mutex_t *mutex_lock);
void			resume_execution(pthread_mutex_t *mutex_lock);
bool			start_threads(t_config *cfg);
void			kill_threads(t_config *config);
void			take_forks(t_config *config, int id);
void			drop_forks(t_config *config);

/* Utils */
struct timeval	add_ms(t_msec ms);
bool			free_config(t_config *config);

#endif
