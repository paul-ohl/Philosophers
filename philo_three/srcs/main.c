/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:55:59 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/28 11:36:47 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "philo_three.h"

int		main(int argc, char **argv)
{
	t_config	*config;

	if (!initialization(argc, argv, &config))
		return (1);
	if (start_threads(config))
		waitpid(-1, NULL, 0);
	for (int a = 0; a < config->philosopher_count; a++)
		printf("pid: %d\n", config->pids[a]);
	printf("on en est là\n");
	kill_threads(config);
	free_config(config);
	return (0);
}
