/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:55:59 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/29 22:49:02 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "philo_three.h"

int		main(int argc, char **argv)
{
	t_config	*config;

	if (!initialization(argc, argv, &config))
		return (1);
	if (start_threads(config, config->philosopher_count - 1))
	{
		if (argc == 6)
			check_for_done_eating(config);
		check_for_death(config);
		sem_wait(config->sem->main_semaphore);
	}
	else
		print_error("Failed to create threads");
	kill_all_threads(config);
	free_config(config);
	return (0);
}
