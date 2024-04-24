/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:05:18 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/24 10:55:29 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	print_strings(t_vec *args, size_t i, int op_n);

int	ft_echo(t_vec *args)
{
	char		**strs;
	size_t		i;
	int			op_n;

	i = 1;
	op_n = 0;
	strs = (char **)args->memory;
	if (!strs[1])
	{
		if (write(1, "\n", 1) < 0)
			return (printf("write failed in echo"), -1);
		return (0);
	}
	if (ft_strncmp(strs[i], "-n", 3) == 0)
	{
		op_n = 1;
		i++;
	}
	if (print_strings(args, i, op_n) < 0)
		return (-1);
	return (0);
}

static int	print_strings(t_vec *args, size_t i, int op_n)
{
	char	**strs;
	int		check;

	strs = (char **)args->memory;
	while (i < args->len)
	{
		// printf("1\nstring%s\n", strs[i]);
		ft_putstr(strs[i], &check);
		if (check < 0)
			return (printf("write errror\n"), -1);  //errmngmt
		if (i < args->len - 1)
		{
			ft_putstr(" ", &check);
			if (check < 0)
				return (printf("write errror\n"), -1);  //errmngmt
		}
		i++;
	}
	if (op_n == 0)
	{
		ft_putstr("\n", &check);
		if (check < 0)
			return (printf("write errror\n"), -1);  //errmngmt
	}
	return (0);
}
