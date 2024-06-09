/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:33:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/07 17:04:39 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_exec(t_exec *exe)
{
	if (exe->cmd_argv)
		free_2d_array(exe->cmd_argv);
	if (exe->pipe_fd)
		free(exe->pipe_fd);
	if (exe->path)
		free(exe->path);
	if (exe->redir.hd_in == YES)
		unlink (exe->redir.hd_file);
	free (exe);
}

void	free_arg(t_shell *arg, int del_hist)
{
	size_t	i;

	i = 0;
	if (!arg || arg->count == 0)
		return ;
	while (i < arg->count)
	{
		if (arg[i].cmd.len != 0)
			vec_free_str(&arg[i].cmd);
		if (arg[i].rdrct.len != 0)
			vec_free_str(&arg[i].rdrct);
		if (arg->exe && arg->exe[i])
			free_exec(arg->exe[i]);
		i++;
	}
	free(arg->exe);
	if (del_hist == YES)
	{
		vec_free_str(&arg->env);
		rl_clear_history();
	}
}

void	close_fds_exit(t_shell *arg, int ret)
{
	size_t	i;
	t_exec	*exe;

	i = 0;
	printf("\n\nret in close_fds_exit: %d\n", ret);
	if (arg)
	{
		while (i < arg->count)
		{
			exe = arg->exe[i];
			if (exe)
				close_fds(exe, YES);
			i++;
		}
		close_other_pipe_fds(arg, -5);
		free_arg(arg, YES);
	}
	exit (ret);
}
