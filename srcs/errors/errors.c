/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:39 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/13 13:34:39 by aneitenb         ###   ########.fr       */
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

int	set_ret_error(t_exec *exe, int ret)
{
	if (access(exe->path, F_OK) == -1 || access(exe->path, X_OK) == 0)
	{
		ret = 127;
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		ret = 126;
		ft_putstr_fd("Permission denied\n", STDERR_FILENO);
	}
	return (ret);
}

int	execve_error(t_exec *exe, char *err_msg, int ret)
{
	ft_putstr_fd("la_shell: ", STDERR_FILENO);
	ft_putstr_fd(exe->cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if ((ret == 2 || ret == 43 || ret == 13))
	{
		if ((ft_strncmp(exe->cmd_argv[0], "/", 1) == 0)
			|| (ft_strncmp(exe->cmd_argv[0], "./", 2) == 0))
			ret = set_ret_error(exe, ret);
		else
		{
			ret = 127;
			ft_putstr_fd("command not found\n", STDERR_FILENO);
		}
	}
	else
		ft_putstr_fd(err_msg, STDERR_FILENO);
	return (ret);
}

void	file_error(char *filename, char *err_msg, t_redir *redir, int flag)
{
	if (redir->file_in != ERRO && flag == 1)
	{
		ft_putstr_fd("la_shell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err_msg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
	else if (redir->file_out != ERRO && flag == 0)
	{
		ft_putstr_fd("la_shell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err_msg, STDERR_FILENO);
		write(STDERR_FILENO, "\n", 1);
	}
}
