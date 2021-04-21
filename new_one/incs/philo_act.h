/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:34:41 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/19 09:26:38 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ACT_H
# define PHILO_ACT_H

typedef struct	s_local
{
	unsigned int	id;
	int				eat_count;
}	t_local;

void	*philo_act(t_config *config);
void	*controller_act(t_config *config);
bool	can_eat(t_config *config, unsigned int id);
bool	is_alive(struct timeval time_of_death);
int		get_time_to_wait(t_msec time_to_check, struct timeval time_of_death);

#endif
