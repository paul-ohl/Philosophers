/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <paulohl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:19:11 by paulohl           #+#    #+#             */
/*   Updated: 2021/01/20 18:56:40 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

#define LOG_LEN 500

int	ft_nbrlen(unsigned int nbr)
{
	int		len;

	if (!nbr)
		return (1);
	len = 0;
	while (nbr)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

void	itoa_in_str(char log[LOG_LEN], int i, unsigned int timestamp)
{
	int		i_svg;

	i_svg = i;
	i += ft_nbrlen(timestamp);
	while (--i >= i_svg)
	{
		log[i] = timestamp % 10 + 48;
		timestamp = timestamp / 10;
	}
}

void	set_timestamp_id(char log[LOG_LEN], struct timeval t_zero, int id, int len)
{
	int		i;
	int		timestamp;
	int		timestamp_len;
	int		id_len;

	i = -1;
	timestamp = get_timestamp(t_zero);
	timestamp_len = ft_nbrlen(timestamp);
	id_len = ft_nbrlen(id);
	while (++i < 10 - timestamp_len)
		log[i] = '0';
	itoa_in_str(log, i, timestamp);
	i = 10;
	while (++i < len - id_len)
		log[i] = '0';
	itoa_in_str(log, i, id);
	log[10] = ' ';
}

int	ft_strcpy(char *dst, const char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}

int	make_action(const int action, int id, t_conf *philo)
{
	char	log[LOG_LEN];
	int		time_id_len;
	int		log_len;

	if (philo->is_over)
		return (1);
	time_id_len = ft_nbrlen(philo->philosopher_count) + 11;
	log_len = time_id_len;
	set_timestamp_id(log, philo->time_zero, id, time_id_len);
	if (action == ACT_EAT)
	{
		log_len += ft_strcpy(log + time_id_len, " has taken a fork\n");
		write(1, log, log_len);
		log_len = time_id_len + ft_strcpy(log + time_id_len, " is eating\n");
	}
	else if (action == ACT_SLEEP)
		log_len += ft_strcpy(log + time_id_len, " is sleeping\n");
	else if (action == ACT_THINK)
		log_len += ft_strcpy(log + time_id_len, " is thinking\n");
	else if (action == ACT_DIE)
		log_len += ft_strcpy(log + time_id_len, " died\n");
	else if (action == ACT_DONE)
		log_len += ft_strcpy(log + time_id_len, " is done eating\n");
	write(1, log, log_len);
	return (0);
}
