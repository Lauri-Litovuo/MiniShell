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

void	parent_process(t_exec *exe, int pipe_fd[], int npipe_fds[], t_shell  *arg)
{
	if (exe->pos == 0)
		close(pipe_fd[1]);
	else if (exe->pos == arg.count)
		close(pipe_fd[0]);
	else
	{
		close(pipe_fd[0]);
		close(npipe_fds[1]);
		pipe_fd[0] = npipe_fds[0];
	}
	close_pipe_fds(arg, exe, exe->pos);
	//free exe?
}

int	child_process(t_shell *arg, t_exec *exe, int pipe_fd[], int npipe_fd[])
{
	int	ret;

	if(exe->pos == 0)
	{
		close (pipe_fds[0]);
		do_redirects(exe, 0, pipe_fd[1]);
	}
	if (exe->pos == arg->count)
	{
		do_redirects(exe, pipe_fd[0], 1);
	}
	else
	{
		close (npipe_fd[0]);
		do_redirects(exe, pipe_fd[0], npipe_fd[1]);
	}
	if (!exe->cmd || !exe->cmd_argv)
		exit(1);
	execute_cmd(exe, arg->env);
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
		set_pipe_fds(exe, arg);
		set_fds(exe->redir, arg)
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

