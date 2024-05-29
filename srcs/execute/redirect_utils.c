/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:05:49 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/29 10:21:05 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_files_and_fd(t_redir *redir)
{
	if (!redir || (!redir->infile && !redir->outfile))
		return (YES);
	if ((redir->infile && redir->fd_in == ERRO)
		|| (redir->outfile && redir->fd_out == ERRO))
		return (ERRO);
	return (YES);
}

int	reset_fds(t_redir *redir)
{
	int	ret;

	ret = 0;
	if (!redir)
		return (0);
	if (redir->orig_fdin != -1)
	{
		if (dup2(redir->orig_fdin, STDIN_FILENO) == -1)
			ret = -1;
		close (redir->orig_fdin);
		redir->orig_fdin = -1;
	}
	if (redir->orig_fdout != -1)
	{
		if (dup2(redir->orig_fdout, STDOUT_FILENO) == -1)
			ret = -1;
		close (redir->orig_fdout);
		redir->orig_fdout = -1;
	}
	return (ret);
}

void	close_fds(t_exec *exe, int reset)
{
	t_redir	*redir;

	redir = &exe->redir;
	if (redir)
	{
		if (redir->fd_in != -1)
			close (redir->fd_in);
		if (redir->fd_out != -1)
			close (redir->fd_out);
		if (reset == YES)
			reset_fds(redir);
	}
}

void	close_all(t_shell *arg)
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
				close_fds(exe, NO);
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
		close_other_pipe_fds(arg, -5);
	}
}
