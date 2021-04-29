/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:09:33 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/29 22:35:00 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "philo_three.h"
#include "philo_act.h"

bool	start_threads(t_config *config, int count)
{
	config->pids[count] = fork();
	if (config->pids[count] == -1)
		return (false);
	else if (config->pids[count] == 0)
	{
		config->id = count + 1;
		philo_act(config);
		exit(0);
	}
	else if (count > 0)
	{
		if (!start_threads(config, count - 1))
		{
			kill(config->pids[count], SIGTERM);
			return (false);
		}
	}
	return (true);
}

void	kill_all_threads(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->philosopher_count)
	{
		kill(config->pids[i], SIGTERM);
		i++;
	}
}

void	check_for_death(t_config *config)
{
	pthread_t	death_checker;

	pthread_create(&death_checker, NULL, wait_for_death_global, config);
	pthread_detach(death_checker);
}

void	check_for_done_eating(t_config *config)
{
	pthread_t	done_checker;

	pthread_create(&done_checker, NULL, wait_for_done_eating_global, config);
	pthread_detach(done_checker);
}
