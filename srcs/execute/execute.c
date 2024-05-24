/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:45:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 12:11:24 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// static void	print_vec(t_vec *vec) //del
// {
// 		for(size_t i = 0; i < vec->len; i++)
// 			printf("ex_env: %s\n", *(char **)vec_get(vec, i));
// }

static int	create_pipes(size_t pipe_count, t_shell *arg)
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

static int	wait_children(int *pids, size_t cmd_count)
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

static int	piping(t_shell *arg, t_vec *env)
{
	int		i;
	t_exec	*exe;
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

int	execute(t_shell *arg, t_vec *env)
{
	int	ret;
	if (!arg || &arg[0].cmd == NULL)
		return (0);
	ret = setup_exe(&arg);
	print_exec(arg);
	// if (ret != 42)
	// 	return (ret);
	// if (piping(arg, env) < -1)
	// 	return (-1);
	// wait_children(&arg->pids, arg->count);
	return (0);
}
