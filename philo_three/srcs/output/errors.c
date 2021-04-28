/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 12:24:07 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/27 10:44:10 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "philo_three.h"

bool	print_error(const char *err)
{
	write(2, err, ft_strlen(err));
	write(2, "Usage: ./philo_two number_of_philosophers time_to_die "
		"time_to_eat time_to_sleep "
		"[number_of_time_each_philosophers_must_eat]\n", 124);
	return (false);
}
