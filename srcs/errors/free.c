/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:46:28 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/16 12:36:43 by aneitenb         ###   ########.fr       */
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
	if (exe->redir.hd_file)
		free (exe->redir.hd_file);
	free (exe);
}

void	free_arg(t_shell *arg, int del_hist)
{
	size_t	i;

	i = -1;
	if (!arg || arg->count == 0)
		return ;
	arg->temp = NULL;
	while (++i < arg->count)
	{
		if (arg->in[i]->cmd->len == 0)
			vec_free(arg->in[i]->cmd);
		else if (arg->in[i]->cmd->len != 0)
			vec_free_str(arg->in[i]->cmd);
		if (arg->in[i]->rdrct->len == 0)
			vec_free(arg->in[i]->rdrct);
		else if (arg->in[i]->rdrct->len != 0)
			vec_free_str(arg->in[i]->rdrct);
		if (arg->exe && arg->exe[i])
			free_exec(arg->exe[i]);
	}
	free(arg->exe);
	arg->exe = NULL;
	if (arg->pids)
		free(arg->pids);
	if (del_hist == YES)
		delete_histories(arg);
}

void	close_fds_exit(t_shell *arg, int ret)
{
	size_t	i;
	t_exec	*exe;

	i = 0;
	if (arg)
	{
		while (i < arg->count)
		{
			exe = arg->exe[i];
			if (exe)
				close_fds(exe);
			i++;
		}
		close_other_pipe_fds(arg, -5);
		free_arg(arg, YES);
	}
	exit (ret);
}

void	delete_histories(t_shell *arg)
{
	size_t	i;
	char	**data;

	i = 0;
	data = (char **)arg->env.memory;
	while (i < arg->env.len)
	{
		free(data[i]);
		i++;
	}
	vec_free(&arg->env);
	rl_clear_history();
}
