/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:15:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/27 12:35:04 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"



int	set_fds(t_redir *redir)
{
	int	ret;

	ret = 0;
	if (!redir)
	return (-1);
	redir->orig_fdin = dup(STDIN_FILENO);
	if (redir->orig_fdin == -1)
		return (perror("dup failed"), -1); //
	redir->orig_fdout = dup(STDOUT_FILENO);
	if (redir->orig_fdout == -1)
		return (perror("dup failed"), -1); //
	if (redir->fd_in != -1)
		if (dup2(redir->fd_in, STDIN_FILENO) == -1)
			ret = error_triple_msg(3, "minishell :", "dup2 :", redir->infile); //
	if (redir->fd_out != -1)
		if (dup2(redir->fd_out, STDOUT_FILENO) == -1)
			ret = error_triple_msg(3, "minishell :", "dup2 :", redir->outfile); //
	
	return (ret);
}

int	set_pipe_fds(t_exec *exe, t_shell *arg)
{
	t_exec	*pre;
	int		prepos;

	prepos = exe->pos - 1;
	pre = arg->exe[prepos];
	if (!exe)
		return (ERR);
	if (pre && pre->redir.pipe_out)
		dup2(pre->pipe_fd[0], STDIN_FILENO);
	if (exe->redir.pipe_out)
		dup2(exe->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(arg, exe, exe->pos);
	return (YES);
}


