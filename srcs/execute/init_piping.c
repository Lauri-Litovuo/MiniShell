/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_piping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:24:23 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/16 10:00:13 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int			piping(t_shell *arg, t_exec *exe);
//static int	push_nulls(t_shell *arg);

int	init_piping(t_shell *arg, t_exec *exe)
{
	exe->paths = (char **)exe->ex_env.paths.memory;
	if (piping(arg, exe) < 0)
		return (-1);
	return (0);
}

int	piping(t_shell *arg, t_exec *exe)
{
	int	i;

	i = 0;
	if (arg->count == 1)
	{
		if (handle_single_arg(&arg[0].rdrct, exe, &arg->env, arg) < 0)
			return (-1);
		return (0);
	}
	/*if (pipe(exe->pipe_fd) == -1)
		return (perror("piping failed"), -1);
	while (i < arg->count)
	{
		if (i == 0)
			exe->pids[i] = first_run(arg, exe, i);
		else if (i == arg->count - 1)
			exe->pids[i] = last_run(arg, exe, i);
		else
			exe->pids[i] = middle_run(arg, exe, i);
		if (exe->pids[i] < 0)
			return (-1);
		i++;
	}*/
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
