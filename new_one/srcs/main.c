/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:55:59 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/18 19:42:48 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		main(int argc, char **argv)
{
	t_config	*config;
	pthread_t	*threads;
	pthread_t	control_thread;

	if (!initialization(argc, argv, &config, &threads))
		return (1);
	// Start threads
	start_threads(config, threads, &control_thread);
	// stop threads
	catch_threads(threads, control_thread, config->philosopher_count);
	// cleanup
	free_config(config, threads);
	return (0);
}
