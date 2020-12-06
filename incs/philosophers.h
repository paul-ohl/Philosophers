/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 09:01:55 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/06 21:56:36 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>

typedef int	t_msec;

typedef struct		s_philosopher
{
	int				philosopher_count;
	int				fork_count;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	int				eat_count;
}					t_philosopher;

#endif
