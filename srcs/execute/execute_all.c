/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:14:42 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 10:51:03 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*int	handle_single_arg(t_vec *rdrct, t_exec *exe, t_vec *env, t_shell *arg)
{
	pid_t	pid;

	exe->cmds = (char **)arg[0].cmd.memory;
	if (!exe->cmds[0])
		return (0);
	pid = fork();
	if (pid == -1)
		return (perror ("Failed to fork"), -1);
	if (pid == 0)
	{
		if (do_redirects(rdrct, &exe->redir, fd) < 0)
			close_and_exit();
		if (isit_child_builtin(exe->cmds[0]) == 1)
		{
			if (launch_builtin(env, &arg->cmd) < 0)
				return (-1);
		}
		else
			if (execve(exe->paths[0], exe->cmds, NULL) == -1)
				perror(exe->cmds[0]);
		exit(0);
	}
	else
	{
		if (isit_parent_builtin(exe->cmds[0]) == 1)
			if (launch_builtin(env, &arg->cmd) < 0)
				return (-1);
		wait(NULL);
	}
	return (0);
}*/













