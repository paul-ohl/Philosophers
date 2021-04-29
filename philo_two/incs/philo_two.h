/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:01:55 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/29 23:26:32 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

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
typedef struct	s_config
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
	bool			is_over;
	int				id;
}				t_config;

bool			print_error(const char *err);
void			print_status(t_config *config, int id, const int act);

bool			is_input_valid(t_config *config);
bool			is_argcount_valid(int argc);
bool			initialization(int ac, char **av, t_config **c, pthread_t **t);

void			stop_execution(pthread_mutex_t *mutex_lock);
void			resume_execution(pthread_mutex_t *mutex_lock);
void			start_threads(t_config *cfg, pthread_t *t, pthread_t *ctrl);
void			catch_threads(pthread_t *t, pthread_t ctrl, int philo_count);
void			take_forks(t_config *config, int id);
void			drop_forks(t_config *config);

struct timeval	add_ms(t_msec ms);
bool			free_config(t_config *config, pthread_t *threads);

#endif
