/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:15:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/04 13:35:13 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	set_fds(t_redir *redir)
{
	int	ret;

	ret = 0;
	if (!redir)
		return (-1);
	if (redir->fd_in != -1)
		if (dup2(redir->fd_in, STDIN_FILENO) == -1)
			ret = error_triple_msg(3, "la_shell :", "dup2 :", redir->infile);
	if (redir->fd_out != -1)
		if (dup2(redir->fd_out, STDOUT_FILENO) == -1)
			ret = error_triple_msg(3, "la_shell :", "dup2 :", redir->outfile);
	return (ret);
}

void	close_other_pipe_fds(t_shell *arg, size_t pos)
{
	size_t	i;
	t_exec	*temp;

	i = 0;
	while (i < arg->count)
	{
		temp = arg->exe[i];
		if (i != pos && temp->pipe_fd)
		{
			close (temp->pipe_fd[0]);
			close (temp->pipe_fd[1]);
		}
		i++;
	}
}

int	set_pipe_fds(t_exec *exe, t_shell *arg)
{
	t_exec	*pre;
	int		prepos;

	prepos = exe->pos - 1;
	if (prepos >= 0)
	{
		pre = arg->exe[prepos];
		if (pre->redir.pipe_out == YES)
			dup2(pre->pipe_fd[0], STDIN_FILENO);
	}
	if (exe->redir.pipe_out == YES)
		dup2(exe->pipe_fd[1], STDOUT_FILENO);
	close_other_pipe_fds(arg, exe->pos);
	return (YES);
}
