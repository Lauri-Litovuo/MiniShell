/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:14:42 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/17 14:54:00 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	handle_single_arg(t_vec *rdrct, t_exec *exe, t_vec *env, t_shell *arg)
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
}

int	child_execute(t_shell *arg, t_exec *exe, int *fd, int i)
{
	int	ret;

	ret = 0;
	ret = do_redirects(arg, &exe->redir, fd);
	if (ret < 0)
		close_and_exit();
	close_fds(&exe->redir)
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
static int	setup_exe(t_exec *exe, t_shell *arg, size_t pos)
{
	
}

int	first_run(t_shell *arg, t_vec *env, int i)
{
	t_exec	exe;
	int		pid;

	pid = setup_exe(&exe, arg, i);
	if (pid != 0)
	{
		handle_single_arg;
		return (pid);
	}
	else
	re
}

int	middle_run(t_shell *arg, t_exec *exe, int *pipe_fd, int i)
{
	
}

int	last_run(t_shell *arg, t_exec *exe, int *pipe_fd, int i)
{
	
}


int	piping(t_shell *arg, t_vec *env)
{
	int	i;

	i = 0;
	if (arg->count == 1)
	{
		setup_exe(&arg, 0);
		if (handle_single_arg(&arg[0].rdrct, exec, &arg->env, arg) < 0)
			return (-1);
		return (0);
	}
	while (i < arg->count)
	{
		setup_exe(&arg, i);
		if (i == 0)
			arg->pids[i] = first_run(&arg[i].exec, &arg->env, i);
		else if (i == arg->count - 1)
			arg->pids[i] = last_run(&arg[i].exec, &fd, i);
		else
			arg->pids[i] = middle_run(&arg[i].exec, fd, i);
		if (arg->pids[i] < 0)
			return (-1);
		free_exe(&arg->exec)
		i++;
	}
	return (0);
}


/*int	wait_children(t_exec *exe, size_t cmd_count)
{
	int	exitcode;
	int	i;

	i = 0;
	exitcode = 0;
	while (i < cmd_count)
	{
		if (exe->pids[i] <= 127)
			exitcode = exe->pids[i];
		else
			exitwaitpid(exe->pids[i], &exitcode, 0);
		i++;
	}
	if (exitcode <= 127)
		return (exitcode);
	return (WEXITSTATUS(exitcode));
}*/

int	execute(t_shell *arg, t_vec *env)
{
	
	if (piping(arg, env) < -1)
	{
		//free_exe(&exe);
		return (-1);
	}
	return (0);
}
