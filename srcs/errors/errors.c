/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:39 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/28 12:02:23 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	error_msg(int flag, char *str, char *specifier)
{
	if (flag == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(specifier, 2);
	}
	else
	{
		ft_putstr_fd(str, 2);
	}
	return (-1);
}

int	error_triple_msg(int flag, char *first, char *sec, char *third)
{
	if (flag == 3)
	{
		ft_putstr_fd(first, 2);
		ft_putstr_fd(sec, 2);
		ft_putstr_fd(third, 2);
		return (0);
	}
	if (flag == 2)
	{
		ft_putstr_fd(first, 2);
		ft_putstr_fd(sec, 2);
		return (0);
	}
	if (flag == 1)
	{
		ft_putstr_fd(first, 2);
		return (0);
	}
	return (-1);
}

int	error_msg_free(int flag, char *str, char *specifier, t_vec *vec)
{
	if (flag == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(specifier, 2);
	}
	if (flag == 1)
	{
		ft_putstr_fd(str, 2);
	}
	if (vec)
		vec_free(vec);
	return (-1);
}

