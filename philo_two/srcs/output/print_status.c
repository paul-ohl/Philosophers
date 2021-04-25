/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ft <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 09:31:19 by ft                #+#    #+#             */
/*   Updated: 2021/04/25 16:26:12 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "philo_two.h"

#define LOG_LEN 100

int	get_timestamp(struct timeval time_zero)
{
	struct timeval	time_now;
	int		timestamp;

	gettimeofday(&time_now, NULL);
	timestamp = (time_now.tv_sec - time_zero.tv_sec) * 1000;
	timestamp += (time_now.tv_usec - time_zero.tv_usec) / 1000;
	return (timestamp);
}

int		write_nb_to_str(char str[LOG_LEN], int number, int size)
{
	int		log_len;

	if (ft_intlen(number) > size)
		size = ft_intlen(number);
	log_len = size;
	while (size--)
	{
		str[size] = number % 10 + '0';
		number /= 10;
	}
	str[log_len] = ' ';
	return (log_len + 1);
}

int		set_timestamp(char log[LOG_LEN], struct timeval time_zero)
{
	int		log_len;
	int		timestamp;

	timestamp = get_timestamp(time_zero);
	log_len = write_nb_to_str(log, timestamp, 9);
	return (log_len);
}

int		set_action(char log[LOG_LEN], int offset, const int action)
{
	int		log_len;

	if (action == ACT_ERROR)
		log_len = ft_strcpy(log + offset, "there was an error\n");
	else if (action == ACT_TAKE_FORK)
		log_len = ft_strcpy(log + offset, "has taken a fork\n");
	else if (action == ACT_EAT)
		log_len = ft_strcpy(log + offset, "is eating\n");
	else if (action == ACT_SLEEP)
		log_len = ft_strcpy(log + offset, "is sleeping\n");
	else if (action == ACT_THINK)
		log_len = ft_strcpy(log + offset, "is thinking\n");
	else if (action == ACT_DIE)
		log_len = ft_strcpy(log + offset, "died\n");
	else if (action == ACT_DONE)
		log_len = ft_strcpy(log + offset, "is done eating\n");
	return (log_len);
}

void	print_status(t_config *config, int id, const int action)
{
	char	log[LOG_LEN];
	int		log_len;

	log_len = set_timestamp(log, config->time_zero);
	log_len += write_nb_to_str(log + log_len, id,
			ft_intlen(config->philosopher_count));
	log_len += set_action(log, log_len, action);
	sem_wait(config->output_semaphore);
	if (!config->is_over)
		write(1, log, log_len);
	sem_post(config->output_semaphore);
}
