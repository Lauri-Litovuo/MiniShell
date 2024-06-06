/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:43 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/06 17:37:01 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	g_signal;

int	init_redir(t_redir *redir)
{
	redir->fd_in = -1;
	redir->fd_out = -1;
	redir->hd_pos = -42;
	redir->re_pos = -42;
	redir->orig_fdin = dup(STDIN_FILENO);
	if (redir->orig_fdin == -1)
		return (perror("dup to in failed"), -1);
	redir->orig_fdout = dup(STDOUT_FILENO);
	if (redir->orig_fdout == -1)
		return (perror("dup to out failed"), -1);
	redir->pipe_out = NO;
	redir->pipe_in = NO;
	redir->file_in = NO;
	redir->file_out = NO;
	redir->hd_in = NO;
	redir->infile = NULL;
	redir->outfile = NULL;
	redir->hd_lim = NULL;
	redir->hd_file = NULL;
	redir->i = -42;
	return (0);
}

int	setup_exe(t_shell *arg)
{
	size_t	i;
	size_t	j;
	t_exec	**exe;
	t_exec	*sub_exe;

	i = 0;
	exe = malloc ((arg->count + 1) * sizeof(t_exec *));
	while (i < arg->count)
	{
		sub_exe = malloc (sizeof(t_exec));
		exe[i] = sub_exe;
		exe[i]->pos = i;
		j = 0;
		exe[i]->cmd_argv = malloc ((arg[i].cmd.len + 1) * sizeof(char *));
		while (j < arg[i].cmd.len)
		{
			exe[i]->cmd_argv[j] = ft_strdup(*(char **)vec_get(&arg[i].cmd, j));
			j++;
		}
		exe[i]->cmd_argv[j] = NULL;
		if (arg[i].cmd.len != 0)
		{
			exe[i]->cmd = *(char **)vec_get(&arg[i].cmd, 0);
			exe[i]->path = get_exec_path(exe[i]->cmd, &arg->env);
			if (exe[i]->path == NULL)
				return (-1);
		}
		exe[i]->ret = 0;
		init_redir(&exe[i]->redir);
		if (arg[i].rdrct.len != 0)
		{
			if (open_files(&arg[i].rdrct, exe[i], arg) < 0)//
				return (-1);//
		}
		if (g_signal == 2)
			arg->exit_code = 1;
		if (sub_exe->pos > 0 && sub_exe->redir.file_in == NO && sub_exe->redir.hd_in == NO)
			sub_exe->redir.pipe_in = 1;
		if (sub_exe->redir.file_out == NO && arg->count > 1 && sub_exe->pos != arg->count - 1)
			sub_exe->redir.pipe_out = 1;
		i++;
	}
	exe[i] = NULL;
	arg->exe = exe;
	return (0);
}
