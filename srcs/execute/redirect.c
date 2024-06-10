/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:15:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/06 21:35:16 by llitovuo         ###   ########.fr       */
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

	i = 0;
	while (i < arg->count)
	{
		ft_fprintf(2, "pos closing %d avoiding %d\n", (int)i, (int)pos);
		if (i != pos && arg->exe[i]->pipe_fd)
		{
			close (arg->exe[i]->pipe_fd[0]);
			close (arg->exe[i]->pipe_fd[1]);
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
		{
			if (dup2(pre->pipe_fd[0], STDIN_FILENO) < -1)
				return (perror("dup2 failed"), -1);
			close(pre->pipe_fd[0]);
		}
	}
	if (exe->redir.pipe_out == YES)
	{
		if (dup2(exe->pipe_fd[1], STDOUT_FILENO) < -1)
			return (perror("dup2 failed"), -1);
		close (exe->pipe_fd[1]);
	}
	close_other_pipe_fds(arg, exe->pos);
	return (YES);
}
