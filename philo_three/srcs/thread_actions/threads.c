/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:09:33 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/26 14:33:36 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_two.h"
#include "philo_act.h"

bool	start_threads(t_config *config, int count)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (false);
	else if (pid == 0)
	{
		philo_act(config);
	}
	else if (count > 0)
	{
		return (start_threads(config, count - 1))
	}
	return (true);
}

void	catch_threads(pthread_t *threads, pthread_t control, int philo_count)
{
	while (philo_count--)
		pthread_join(threads[philo_count], NULL);
	pthread_join(control, NULL);
}
