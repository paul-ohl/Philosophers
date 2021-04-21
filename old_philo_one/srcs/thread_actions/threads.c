/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:09:33 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/19 15:16:26 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include "philo_act.h"

void	start_threads(t_config *config, pthread_t *threads, pthread_t *control)
{
	unsigned int	i;

	i = -1;
	while (++i < config->philosopher_count)
		pthread_create(&(threads[i]), NULL, (void*(*)(void*))philo_act, config);
	pthread_create(control, NULL, (void*(*)(void*))controller_act, config);
}

void	catch_threads(pthread_t *threads, pthread_t control, int philo_count)
{
	while (philo_count--)
		pthread_join(threads[philo_count], NULL);
	pthread_join(control, NULL);
}
