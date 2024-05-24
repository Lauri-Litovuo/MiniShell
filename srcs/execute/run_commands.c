/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:07:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 16:33:22 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"


int	child_execute(t_shell *arg, t_exec *exe, int *fd, int i)
{
	int	ret;

	ret = 0;
	ret = do_redirects(arg, &exe->redir, fd);
	if (ret < 0)
		close_and_exit();
	close_fds(&exe->redir);
	if (isit_child_builtin(exe->cmds[i]) == 1)
	{
		ret = launch_builtin(&arg->env, &arg->cmd, &exe->redir);
		if (ret < 0)
			return (ret);
	}
	else
		if (execve(exe->paths[0], &exe->cmds[0][0], NULL) == -1)
			perror(exe->cmds[0][0]);
	else
	{
		close_and_exit();
	}
}

int	first_run(t_exec *exe, t_vec *env)
{
	t_exec	exe;
	int		pid;

}



int	middle_run(t_exec *exe, t_vec *env)
{
	
}

int	last_run(t_exec *exe, t_vec *env, t_shell *arg)
{
	pid_t	pid;

	if (!exe)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (perror ("Failed to fork"), -1);
	if (pid == 0)
	{
		if (do_redirects(rdrct, &exe->redir, fd) < 0)
			close_and_exit();
		child_execute(exe, env);
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
}

