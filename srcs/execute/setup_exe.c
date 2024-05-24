/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:43 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 10:30:37 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	init_redir(t_redir *redir)
{
	redir->fd_in = -42;
	redir->fd_out = -42;
	dup2(redir->orig_fdin, STDIN_FILENO);
	dup2(redir->orig_fdout, STDOUT_FILENO);
	redir->hd_pos = -42;
	redir->re_pos = -42;
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
}

static int	setup_exe(t_shell *arg)
{
	size_t	i;
	t_exec	exe;

	i = 0;
	if (vec_new(&arg->exe, arg->count, sizeof(t_exec *)) < 0)
		return (-1);
	while (i < &arg->count)
	{
		exe.pos = i;
		exe.cmd_argv = (char **)arg[i].cmd.memory;
		exe.cmd = *(char **)vec_get(&arg[i].cmd, 0);
		exe.path = get_exec_path(&exe.cmd, &arg->env);
		if (exe.path == NULL)
			return (-1);
		exe.ret = 0;
		init_redir(&exe.redir);
		open_files(&arg[i].rdrct, exe.redir, &arg->env);
		if (vec_push(&arg->exe, &exe) < 0)
			return (-1);
	}
	return (0);
}
