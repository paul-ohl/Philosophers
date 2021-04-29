/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:01:55 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/29 23:34:26 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

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
	pthread_mutex_t	*forks;
	pthread_mutex_t	main_mutex;
	struct timeval	time_zero;
	struct timeval	*time_of_death;
	bool			is_over;
	int				id;
}				t_config;

bool			print_error(const char *err);
void			print_status(t_config *config, int id, const int act);

bool			is_argcount_valid(int argc);
bool			is_input_valid(t_config *config);
bool			initialization(int ac, char **av, t_config **c, pthread_t **t);

void			stop_execution(pthread_mutex_t *mutex_lock);
void			resume_execution(pthread_mutex_t *mutex_lock);
void			start_threads(t_config *cfg, pthread_t *t, pthread_t *ctrl);
void			catch_threads(pthread_t *t, pthread_t ctrl, int philo_count);
void			take_forks(t_config *config, int id);
void			drop_forks(t_config *config, int id);

struct timeval	add_ms(t_msec ms);
bool			free_config(t_config *config, pthread_t *threads);

#endif
