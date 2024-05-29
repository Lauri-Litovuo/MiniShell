/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:45:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/29 12:31:05 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// static void	print_vec(t_vec *vec) //del
// {
// 		for(size_t i = 0; i < vec->len; i++)
// 			printf("ex_env: %s\n", *(char **)vec_get(vec, i));
// }


static int	wait_children(t_shell *arg)
{
	int		status;
	int		temp;
	pid_t	wait_pid;
	t_exec	*exe;
	size_t	i;

	i = 0;
	wait_pid = 0;
	temp = 0;
	close_other_pipe_fds(arg, -5);
	while (i < arg->count)
	{
		exe = arg->exe[i];
		close_fds(arg->exe[i], NO);
		if (i == 0)
			reset_fds(&exe->redir);
		else
		{
			close (exe->redir.orig_fdin);
			exe->redir.orig_fdin = -1;
			close (exe->redir.orig_fdout);
			exe->redir.orig_fdout = -1;
		}
		i++;
	}
	while (wait_pid != -1 || errno != ECHILD)
	{
		wait_pid = waitpid(-1, &status, 0);
		if (wait_pid == arg->pids)
			temp = status;
		continue ;
	}
	if (WIFSIGNALED(temp) != 0)
		status = 128 + WTERMSIG(temp);
	else if (WIFEXITED(temp) != 0)
		status = WEXITSTATUS(temp);
	else
		status = temp;
	return (status);
}

static int	piping(t_shell *arg)
{
	size_t	i;

	i = 0;
	arg->pids = -1;
	while (i < arg->count)
	{
		arg->pids = fork();
		if (arg->pids == -1)
			return (-1);
		else if (arg->pids == 0)
			run_command(arg, arg->exe[i]);
		i++;
	}
	return (wait_children(arg));
}

static int	create_pipes(size_t pipe_count, t_shell *arg)
{
	size_t	i;
	int		*fd;
	t_exec	*exe;

	i = 0;
	while (i < pipe_count + 1)
	{
		exe = arg->exe[i];
		fd = malloc(sizeof(fd) * 2);
		if (!fd || pipe(fd) < 0)
		{
			free_arg(arg, NO);
			return (-1);
		}
		exe->pipe_fd = fd;
		i++;
	}
	return (0);
}

int	execute(t_shell *arg)
{
	int	ret;

	ret = setup_exe(arg);
	if (ret == -1)
		return (ret);
	if (create_pipes(arg->pipe_count, arg) < -1)
	{
		ft_fprintf(2, "minishell: pipe creation failed");
		return (-1);
	}
	if (arg->count == 1 && isit_builtin(arg->exe[0]->cmd, 0) != 0
		&& check_files_and_fd(&arg->exe[0]->redir) == YES)
	{
		set_fds(&arg->exe[0]->redir);
		ret = launch_builtin(&arg->env, arg->exe[0], arg);
		close_fds(arg->exe[0], YES);
		return (ret);
	}
	if (piping(arg) < -1)
		return (-1);
	return (ret);
}
