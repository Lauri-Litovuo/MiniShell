/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:39 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/03 16:28:26 by llitovuo         ###   ########.fr       */
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

int	execve_error(t_exec *exe, char *err_msg, int ret)
{
	ft_putstr_fd("la_shell: ", STDERR_FILENO);
	ft_putstr_fd(exe->cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (ret == 2 && access(exe->path, F_OK) == -1)
		ft_putstr_fd("command not found", STDERR_FILENO);
	else
		ft_putstr_fd(err_msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	return (ret);
}
