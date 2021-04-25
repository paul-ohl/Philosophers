/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:21:55 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/22 12:46:14 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_two.h"

bool	is_input_valid(t_config *config)
{
	if (!config)
		return (print_error("Malloc error\n"));
	if (config->philosopher_count <= 0)
	{
		free_config(config, NULL);
		return (print_error("There can't be 0 or less philsosophers\n"));
	}
	else if (config->time_to_die < 0 || config->time_to_sleep < 0
		|| config->time_to_eat < 0)
	{
		free_config(config, NULL);
		return (print_error("Timings can't be negative numbers\n"));
	}
	return (true);
}

bool	is_argcount_valid(int argc)
{
	if (argc < 5 || argc > 6)
		return (print_error("Wrong number of arguments\n"));
	return (true);
}
