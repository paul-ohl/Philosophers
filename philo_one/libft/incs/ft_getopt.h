/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulohl <pohl@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:04:59 by paulohl           #+#    #+#             */
/*   Updated: 2021/04/29 23:07:02 by ft               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_H
# define FT_GETOPT_H

typedef struct	s_opt
{
	char	*optarg;
	int		optind;
	int		optopt;
	int		opterr;
	int		optreset;
}				t_opt;

int				ft_getopt(t_opt *opts, int argc, char *argv[], char *optstring);

#endif
