/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:45:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/06 21:44:51 by llitovuo         ###   ########.fr       */
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
	while (i < arg->count)
	{
		exe = arg->exe[i];
		close_fds(arg->exe[i], NO);
		i++;
	}
	close_other_pipe_fds(arg, 4000);
	signal(SIGINT, SIG_IGN);
	while (wait_pid != -1 || errno != ECHILD)
	{
		wait_pid = waitpid(-1, &status, 0);
		//printf("waitpid: %d\n", wait_pid);
		if (wait_pid == arg->pids)
			temp = status;
		continue ;
	}
	if (WIFEXITED(temp) == 1)
		arg->exit_code = WEXITSTATUS(temp);
	else if (WIFSIGNALED(temp))
		arg->exit_code = 128 + WTERMSIG(temp);
	// if (arg->exit_code == 130)
	// 		printf("\n");
	// if (arg->exit_code == 131)
	// 		printf("Quit: 3\n");
	signals_default();
	return (arg->exit_code);
}

static int	piping(t_shell *arg)
{
	size_t	i;

	i = 0;
	arg->pids = ft_memset(arg->pids, (-1), arg->count);
	while (arg->pids[i] != 0 && i < arg->count)
	{
		arg->pids = fork();
		if (arg->pids[i] == -1)
			return (-1);
		else if (arg->pids[i] == 0)
		{
			signals_child();
			run_command(arg, arg->exe[i]);
		}
		signal(SIGQUIT, SIG_IGN);
		i++;
	}
	return (0);
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
			set_fds(&arg->exe[0]->redir);
			ret = launch_builtin(&arg->env, arg->exe[0], arg);
			close_fds(arg->exe[0], YES);
			return (ret);
		}
	}
	if (piping(arg) < -1)
		return (-1);
	ret = wait_children(arg);
	arg->exit_code = ret;
	return (ret);
}
