/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:45:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/12 17:09:27 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	close_for_waitpid(t_shell *arg)
{
	size_t	i;

	i = 0;
	close_other_pipe_fds(arg, -5);
	while (i < arg->count)
	{
		close_fds(arg->exe[i]);
		i++;
	}
}

static int	wait_children(t_shell *arg)
{
	int		status;
	pid_t	wait_pid;
	size_t	i;

	wait_pid = 0;
	close_for_waitpid(arg);
	i = 0;
	while (arg->pids[i] != -1)
	{
		wait_pid = waitpid(arg->pids[i], &status, 0);
		if (wait_pid == -1)
			continue ;
		i++;
	}
	if (WIFSIGNALED(status) != 0)
		arg->exit_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status) != 0)
		arg->exit_code = WEXITSTATUS(status);
	else
		arg->exit_code = status;
	if (arg->exit_code == 130)
		printf("\n");
	if (arg->exit_code == 131)
		printf("Quit: 3\n");
	return (arg->exit_code);
}

static int	piping(t_shell *arg)
{
	size_t	i;

	i = 0;
	arg->pids = ft_calloc(arg->count + 1, sizeof(int));
	arg->pids[arg->count] = -1;
	while (i < arg->count)
	{
		arg->pids[i] = fork();
		if (arg->pids[i] == -1)
			return (-1);
		else if (arg->pids[i] == 0)
		{
			signals_child();
			run_command(arg, arg->exe[i]);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
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
	while (i < pipe_count)
	{
		exe = arg->exe[i];
		fd = malloc(sizeof(int) * 2);
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

	arg->orig_fd[0] = dup(STDIN_FILENO);
	arg->orig_fd[1] = dup(STDOUT_FILENO);
	ret = setup_exe(arg);
	if (ret < 0)
		return (ret);
	if (create_pipes(arg->pipe_count, arg) < -1)
		return (-1);
	if (arg->count == 1 && check_files_and_fd(&arg->exe[0]->redir) == YES)
	{
		if (isit_builtin(arg->exe[0]->cmd, 0) == -1)
			return (0);
		else if (isit_builtin(arg->exe[0]->cmd, 0) == INT_MIN)
		{
			ret = execute_single_builtin(arg);
			return (ret);
		}
	}
	ret = piping(arg);
	signals_default();
	reset_fds(arg->orig_fd);
	arg->exit_code = ret;
	return (ret);
}
