/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:05:49 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/28 14:36:41 by llitovuo         ###   ########.fr       */
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

void	close_other_pipe_fds(t_shell *arg, size_t pos)
{
	size_t	i;
	t_exec	*temp;

	i = 0;
	while (i < arg->count)
	{
		temp = arg->exe[i];
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
		printf("resetting origin\n"); //
		if (dup2(redir->orig_fdin, STDIN_FILENO) == -1)
			ret = -1;
		close (redir->orig_fdin);
		redir->orig_fdin = -1;
	}
	if (redir->orig_fdout != -1)
	{
		printf("resetting origout\n"); //
		if (dup2(redir->orig_fdout, STDOUT_FILENO) == -1)
			ret = -1;
		close (redir->orig_fdout);
		printf("stdout %d\n", STDOUT_FILENO);
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
void	free_arg(t_shell *arg, int del_hist)
{
	free (arg);
	if (del_hist == 1)
	{
		//remove history;
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
			{
				close_fds(exe, YES);
			}
			i++;
		}
		close_other_pipe_fds(arg, -1);
	}
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
				close_fds(exe, YES);
			i++;
		}
		close_other_pipe_fds(arg, -1);
		free_arg(arg, NO);
	}
	exit (ret);
}
