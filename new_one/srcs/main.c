/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:55:59 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/07 14:21:49 by paulohl          ###   ########.fr       */
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
	return (0);
}
