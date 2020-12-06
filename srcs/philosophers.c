/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 13:34:54 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/06 13:40:44 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosophers.h"

void	*my_turn(void *arg)
{
	int		*w;

	w = malloc(sizeof(int));
	for (int i = 0; i < 8; i++)
	{
		sleep(1);
		printf("%d: My turn!\n", i);
	}
	arg = 0;
	*w = 13;
	return (w);
}

int		is_alive(t_time time_of_death)
{
	struct timeval	current_time;

	if (!gettimeofday(&current_time, NULL))
		return (-1);
	if (current_time
}

void	*philosopher(void *arg)
{
	t_philosopher	*philosopher = (t_philosopher *)arg;
	int				fork_count;

	fork_count = 3;
	while (1)
	{
		while (is_alive(philosopher->time_of_death) && fork_count < 2)
			usleep(10);
		printf("Eat for %dsecs\n", timings->eat_time);
		sleep(timings->eat_time);
		printf("Sleep for %dsecs\n", timings->sleep_time);
		sleep(timings->sleep_time);
		printf("Think for %dsecs\n", timings->think_time);
		sleep(timings->think_time);
	}
	return (NULL);
}

int		main()
{
	t_timings	timings;
	/* pthread_t	newthread; */

	timings.eat_time = 1;
	timings.sleep_time = 3;
	timings.think_time = 2;
	philosopher(&timings);
	/* pthread_create(&newthread, NULL, my_turn, NULL); */
	/* pthread_join(newthread, (void *)&my_w); */
}
