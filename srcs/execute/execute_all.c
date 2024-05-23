/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:14:42 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/23 13:14:15 by llitovuo         ###   ########.fr       */
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


int	first_run(t_exec *exe, t_vec *env)
{
	t_exec	exe;
	int		pid;

}



int	middle_run(t_exec *exe, t_vec *env)
{
	
}

int	last_run(t_exec *exe, t_vec *env)
{
	
}

int	create_pipes(size_t pipe_count, t_shell *arg)
{
	size_t	i;
	int		*fd;
	t_exec	*exe;

	i = 0;
	while (i < pipe_count)
	{
		exe = &arg[i].exe;
		if (exe->redir.pipe_out || exe->redir.pipe_in)
		fd = malloc(sizeof(fd) * 2);
		if (!fd || pipe(fd) < 0)
			return (-1);
		exe->pipe_fd = fd;
	}
	return (0);
}
int	piping(t_shell *arg, t_vec *env)
{
	int	i;
	t_exec *exe;
	int		stat_fd[2];

	i = 0;

	if (create_pipes(arg->pipe_count, &arg) < 0)
		return (-1); //
	i = 0;
	arg->pids = calloc (arg->count, sizeof(int));
	while (i < arg->count)
	{
		exe = &arg[i].exe;
		if (i == 0)
			arg->pids[i] = first_run(&exe, &env);
		else if (i == arg->count - 1)
			arg->pids[i] = last_run(exe, env);
		else
			arg->pids[i] = middle_run(exe, env);
		if (arg->pids[i] < 0)
			return (-1);
		i++;
	}
	return (0);
}


int	wait_children(int *pids, size_t cmd_count)
{
	int	exitcode;
	int	i;

	i = 0;
	exitcode = 0;
	while (i < cmd_count)
	{
		if (pids[i] <= 127)
			exitcode = pids[i];
		else
			exitwaitpid(pids[i], &exitcode, 0);
		i++;
	}
	if (exitcode <= 127)
		return (exitcode);
	return (WEXITSTATUS(exitcode));
}



int	execute(t_shell *arg, t_vec *env)
{
	int	ret;
	if (!arg || &arg[0].cmd == NULL)
		return (0);
	ret = setup_exe(&arg);
	if (ret != 42)
		return (ret);
	if (piping(arg, env) < -1)
		return (-1);
	wait_children(&arg->pids, arg->count);
	return (0);
}
