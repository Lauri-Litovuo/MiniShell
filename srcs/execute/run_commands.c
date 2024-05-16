/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:07:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/16 10:14:35 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	handle_single_arg(t_vec *rdrct, t_exec *exe, t_vec *env, t_shell *arg)
{
	pid_t	pid;

	exe->cmds = (char **)arg[0].cmd.memory;
	if (do_redirects(rdrct, &exe->redir, exe->heredocs) < 0)
		return (-1);
	if (!exe->cmds[0])
		return (0);
	pid = fork();
	if (pid == -1)
		return (perror ("Failed to fork"), -1);
	if (pid == 0)
	{
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
/*
int	child_execute(t_shell *arg, t_exec *exe, int i)
{
	if (isit_child_builtin(exe->cmds[0][0]) == 1)
	{
		if (launch_builtin(env, &arg->cmd) < 0)
			return (-1);
	}
	else
		if (execve(exe->paths[0], &exe->cmds[0][0], NULL) == -1)
			perror(exe->cmds[0][0]);
}

int	first_run(t_shell *arg, t_exec *exe, int i)
{
	pid_t	pid;

	do_redirects(arg, exe->redir, exe->heredocs);
	pid = fork();
	if (pid == -1)
	{
		perror ("Failed to fork");
		return (-1);
	}
	if (pid == 0)
	{
		child_execute(arg, exe, i);
	}
	parent_execute(arg, exe, i);
	return (pid);
}

int	middle_run(t_shell *arg, t_exec *exe, i)
{
	
}

int	last_run(arg, exe, i)
{
	
}*/
