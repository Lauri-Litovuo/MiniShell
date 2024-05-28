/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:45:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/28 15:12:41 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// static void	print_vec(t_vec *vec) //del
// {
// 		for(size_t i = 0; i < vec->len; i++)
// 			printf("ex_env: %s\n", *(char **)vec_get(vec, i));
// }


static int	wait_children(int *pids, size_t cmd_count)
{
	int		exitcode;
	size_t	i;

	i = 0;
	exitcode = 0;
	while (i < cmd_count)
	{
		if (pids[i] <= 127)
			exitcode = pids[i];
		else
			waitpid(pids[i], &exitcode, 0);
		i++;
	}
	if (exitcode <= 127)
		return (exitcode);
	return (WEXITSTATUS(exitcode));
}

static int	piping(t_shell *arg)
{
	size_t	i;
	int		ret;

	i = 0;
	arg->pids = ft_calloc(arg->count, sizeof(int));
	while (i < arg->count && arg->pids)
	{
		arg->pids[i] = fork();
		if (arg->pids[i] == -1)
			return (-1); // fork failed
		else if (arg->pids[i] == 0)
			run_command(arg, arg->exe[i]); // ret = ?
		i++;
	}
	close_all(arg);
	ret = wait_children(arg->pids, arg->count);
	return (ret);
}

static int	create_pipes(size_t pipe_count, t_shell *arg)
{
	size_t	i;
	int		*fd;
	t_exec	*exe;

	i = 0;
	while (i <= pipe_count)
	{
		exe = arg->exe[i];
		fd = malloc(sizeof(fd) * 2);
		if (!fd || pipe(fd) < 0)
			return (-1);
		exe->pipe_fd = fd;
	}
	return (0);
}

int	execute(t_shell *arg)
{
	int	ret;

	ret = setup_exe(arg);
	if (ret == -1)
		return (ret);
	print_exec(arg->exe);
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
		print_exec(&arg->exe[0]); //
		close_fds(arg->exe[0], YES);
		return (ret);
	}
	printf("2\n");
	if (piping(arg) < -1)
	 	return (-1);
	return (ret);
}
