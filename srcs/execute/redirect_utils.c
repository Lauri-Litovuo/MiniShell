/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:05:49 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/27 12:36:11 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_files_and_fd(t_redir *redir)
{
	if (!redir || (!redir->infile && !redir->outfile))
		return (YES);
	if ((redir->infile && redir->fd_in == ERRO)
		|| (redir->outfile && redir->fd_out == ERRO))
		return (ERR);
	return (YES);
}

void	close_other_pipe_fds(t_shell *arg, t_exec *exe, size_t pos)
{
	size_t	i;
	t_exec	*temp;

	i = 0;
	while (i < &arg->count)
	{
		temp = &arg[i];
		if (i != pos && temp->pipe_fd != 0)
		{
			close (temp->pipe_fd[0]);
			close (temp->pipe_fd[1]);
		}
		i++;
	}
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
		if (dup2(redir->orig_fdout, STDIN_FILENO) == -1)
			ret = -1;
		close (redir->orig_fdout);
		redir->orig_fdout = -1;
	}
	return (ret);
}

void	write_file_error(char *filename, char *errno)
{
	write (2, "minishell: ", 7);
	ft_putstr_fd (filename, 2);
	write (2, ": ", 2);
	ft_putstr_fd (errno, 2);
}
