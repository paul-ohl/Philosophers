/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:09:33 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/28 11:58:38 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "philo_three.h"
#include "philo_act.h"

void	start_pthread(t_config *config, int id)
{
	pthread_t	thread;

	config->id = id;
	pthread_create(&thread, NULL, (void*(*)(void *))philo_act, config);
	pthread_join(thread, NULL);
	printf("HI\n");
}

bool	start_threads(t_config *config)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < config->philosopher_count)
	{
		pid = fork();
		if (pid == -1)
			return (false);
		else if (pid == 0)
		{
			printf("Creating thread %d\n", i);
			start_pthread(config, i + 1);
		}
		else
			config->pids[i] = pid;
		i++;
	}
	return (true);
}

void	wait_threads(t_config *config)
{
	int		i;

	i = 0;
	while (i < config->philosopher_count)
	{
		waitpid(config->pids[i], NULL, 0);
		i++;
	}
}

void	kill_threads(t_config *config)
{
	while (config->philosopher_count--)
	{
		kill(config->pids[config->philosopher_count], SIGKILL);
	}
}
