/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 10:19:11 by paulohl           #+#    #+#             */
/*   Updated: 2020/12/11 11:00:20 by paulohl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

#define LOG_LEN 500

int		ft_nbrlen(unsigned int nbr)
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

void	itoa_in_str(char log[LOG_LEN], int i, unsigned timestamp)
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

void	set_timestamp_id(char log[LOG_LEN], t_tv t_zero, int id, int len)
{
	int		i;
	int		timestamp;

	i = -1;
	timestamp = get_timestamp(t_zero);
	while (++i < 10 - ft_nbrlen(timestamp))
		log[i] = '0';
	itoa_in_str(log, i, timestamp);
	i = 10;
	while (++i < len - ft_nbrlen(id))
		log[i] = '0';
	itoa_in_str(log, i, id);
	log[10] = ' ';
}

int		ft_strcpy(char *dst, const char *src)
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

int		make_action(int action, int id, t_philosopher *philosopher)
{
	char	log[LOG_LEN];
	int		len;

	len = ft_nbrlen(philosopher->philosopher_count) + 11;
	set_timestamp_id(log, philosopher->time_zero, id, len);
	if (action == ACT_EAT)
	{
		len = ft_strcpy(log + 12, " has taken a fork\n");
		write(1, log, len + 12);
		len = ft_strcpy(log + 12, " is eating\n");
	}
	else if (action == ACT_SLEEP)
		len = ft_strcpy(log + 12, " is sleeping\n");
	else if (action == ACT_THINK)
		len = ft_strcpy(log + 12, " is thinking\n");
	else if (action == ACT_DIE)
		len = ft_strcpy(log + 12, " died\n");
	else if (action == ACT_DONE)
		len = ft_strcpy(log + 12, " is done eating\n");
	write(1, log, len + 12);
	return (0);
}
