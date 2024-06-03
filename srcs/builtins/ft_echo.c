/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:05:18 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/03 16:18:16 by llitovuo         ###   ########.fr       */
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
	if (args->len == 1)
	{
		if (write(1, "\n", 1) < 0)
			return (-1);
		return (0);
	}
	if (ft_strncmp(strs[1], "-n", 3) == 0)
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
		ft_putstr(strs[i], &check);
		if (i < args->len - 1)
			ft_putstr(" ", &check);
		i++;
	}
	if (op_n == 1)
		return (0);
	ft_putstr("\n", &check);
	return (0);
}
