/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:51:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/21 15:54:22 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	write_file_error(char *filename, char *errno)
{
	write (2, "minishell: ", 7);
	ft_putstr_fd (filename, 2);
	write (2, ": ", 2);
	ft_putstr_fd (errno, 2);
}

int	open_infiles(t_vec *rdrct, t_redir *redir, int pos)
{
	char	*filename;
	int		temp;
	int		pos_hold;

	temp = -42;
	pos_hold = pos - 1;
	filename = *(char **)vec_get(rdrct, pos);
	temp = open(filename, O_RDONLY);
	pos++;
	while (pos < rdrct->len && temp != -1)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, i), "<", 2) == 0)
		{
			pos_hold = pos;
			pos++;
			filename = *(char **)vec_get(rdrct, pos);
			temp = open(filename, O_RDONLY);
		}
		pos++;
	}
	redir->infile = filename; // remove if uneccessary
	if (pos_hold > redir->hd_pos)
		redir->fd_in = temp;
	redir->file_in = ERR;
	if (temp == ERR)
		return (write_file_error(filename, strerror(errno)), -1);
	redir->file_in = YES;
	return (0);
}

int	get_fdout(t_vec *rdrct, t_redir *redir, int pos)
{
	char	*filename;
	int		temp;

	temp = -42;
	filename = *(char **)vec_get(rdrct, pos + 1);
	if (ft_strncmp(*(char **)vec_get(rdrct, pos), ">>", 3))
		temp = open (filename, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		temp = open (filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
	pos++;
	while (pos < rdrct->len && temp != -1)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, i), ">>", 3))
		{
			pos++;
			filename = *(char **)vec_get(rdrct, pos);
			temp = open (filename, O_RDWR | O_APPEND | O_CREAT, 0644);
		}
		else if (ft_strncmp(*(char **)vec_get(rdrct, pos), ">", 2) == 0)
		{
			pos++;
			filename = *(char **)vec_get(rdrct, pos);
			temp = open (filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		pos++;
	}
	redir->outfile = filename; // remove if uneccessary
	redir->fd_out = temp;
	redir->file_out = ERR;
	if (temp == ERR)
		return (write_file_error(filename, strerror(errno)), -1);
	redir->file_out = YES;
	return (0);
}


int	setup_and_open_files(t_vec *rdrct, t_redir *redir)
{
	int	i;

	i = 0;
	while (i < rdrct->len)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, i), "<", 2) == 0 && redir->file_in == NO)
			redir->file_in = open_infiles(rdrct, redir, i++);
		else if (redir->file_out == NO && ((ft_strncmp(*(char **)vec_get(rdrct, i), ">", 2) == 0) 
		|| ft_strncmp(*(char **)vec_get(rdrct, i), ">>", 3) == 0))
			redir->file_out = open_outfile(rdrct, redir, i);
		i++;
	}
	return (0);
}

int	setup_fds(t_vec *rdrct, t_redir *redir, t_exec *pre, t_vec *env)
{
	if (pre && pre->redir->pipe_out == YES)
		redir->pipe_in == YES;
	dup2(redir->orig_fdin, STDIN_FILENO);
	dup2(redir->orig_fdout, STDOUT_FILENO);
	if (rdrct->len != 0)
	{
		check_for_heredoc(rdrct, redir, env);
		setup_and_open_files(rdrct, redir);
	}
}

int	open_files(t_vec *rdrct, t_redir *redir, t_exec *pre, t_vec *env)
{
	setup_fds(rdrct, redir, pre);
	check_redirs(rdrct, redir);
	if (redir->file_in == 0 && redir->hd_in == 0)
		redir->pipe_in = 1;
	if (redir->file_out == 0 && redir->hd_out == 0)
		redir->pipe_out = 1;
}


void	init_redir(t_redir *redir)
{
	fd_in = -42;
	fd_out = -42;
	orig_fdin = -42;
	orig_fdout = -42;
	hd_pos = -42;
	pipe_out = NO;
	pipe_in = NO;
	file_in = NO;
	file_out = NO;
	hd_in = NO;
	infile = NULL;
	outfile = NULL;
	hd_lim = NULL;
	hd_file = NULL;
}