/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:05:49 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/12 17:38:14 by llitovuo         ###   ########.fr       */
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

int	reset_fds(int orig_fd[2])
{
	int	ret;

	ret = 0;
	if (dup2(orig_fd[0], STDIN_FILENO) == -1)
		ret = -1;
	close (orig_fd[0]);
	if (dup2(orig_fd[1], STDOUT_FILENO) == -1)
		ret = -1;
	close (orig_fd[1]);
	return (ret);
}

void	close_fds(t_exec *exe)
{
	t_redir	*redir;

	redir = &exe->redir;
	if (redir)
	{
		if (redir->fd_in != -1)
			close (redir->fd_in);
		if (redir->fd_out != -1)
			close (redir->fd_out);
	}
}

void	close_all(t_shell *arg, int pos)
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
		close_other_pipe_fds(arg, pos);
	}
}
