/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:51:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/27 11:18:46 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	open_infiles(t_vec *rdrct, t_redir *redir, size_t pos)
{
	char	*filename;
	int		fd;

	fd = -42;
	filename = *(char **)vec_get(rdrct, pos);
	fd = open(filename, O_RDONLY);
	pos++;
	while (fd != -1 && pos < rdrct->len)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, pos), "<", 2) == 0)
		{
			close(fd);
			redir->re_pos = pos;
			pos++;
			filename = *(char **)vec_get(rdrct, pos);
			fd = open(filename, O_RDONLY);
		}
		pos++;
	}
	redir->infile = filename;
	if (redir->re_pos > redir->hd_pos)
		redir->fd_in = fd;
	redir->file_in = ERRO;
	if (fd == ERRO)
		return (ft_fprintf(2, "minishell : %s: Permission denied.", filename), -1); //
	redir->file_in = YES;
	return (redir->file_in);
}

static int	open_outfiles(t_vec *rdrct, t_redir *redir, size_t pos)
{
	redir->i = -42;
	redir->outfile = *(char **)vec_get(rdrct, pos + 1);
	if (ft_strncmp(">", *(char **)vec_get(rdrct, pos), 2) == 0)
		redir->i = open (redir->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else
		redir->i = open (redir->outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
	pos++;
	while (pos < rdrct->len && redir->i != -1)
	{
		if (ft_strncmp(">", *(char **)vec_get(rdrct, pos), 2) == 0)
		{
			close(redir->i);
			pos++;
			redir->outfile = *(char **)vec_get(rdrct, pos);
			redir->i = open(redir->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		else if (ft_strncmp(">>", *(char **)vec_get(rdrct, pos), 3) == 0)
		{
			close (redir->i);
			pos++;
			redir->outfile = *(char **)vec_get(rdrct, pos);
			redir->i = open(redir->outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
		}
		pos++;
	}
	redir->fd_out = redir->i;
	redir->file_out = ERRO;
	if (redir->i == ERRO)
		return (ft_fprintf(2, "minishell : %s: Permission denied.", redir->outfile), ERRO); //
	redir->file_out = YES;
	return (YES);
}


int	setup_and_open_files(t_vec *rdrct, t_redir *redir)
{
	size_t	i;

	i = 0;
	while (i < rdrct->len)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, i), "<", 2) == 0
			&& redir->file_in == NO)
		{
			redir->re_pos = i;
			i++;
			redir->file_in = open_infiles(rdrct, redir, i);
		}
		else if (redir->file_out == NO
			&& ((ft_strncmp(*(char **)vec_get(rdrct, i), ">", 2) == 0)
				|| ft_strncmp(*(char **)vec_get(rdrct, i), ">>", 3) == 0))
		{
			redir->file_out = open_outfiles(rdrct, redir, i);
		}
		i++;
	}
	return (0);
}

int	open_files(t_vec *rdrct, t_redir *redir, t_vec *env, size_t count)
{
	if (rdrct->len != 0)
	{
		if (check_for_heredoc(rdrct, redir, env, rdrct->len) < 0)
			return (ft_fprintf(2, "minishell : heredoc failed."), -1); //
		if (setup_and_open_files(rdrct, redir) < 0)
			return (-1);
	}
	if (redir->file_in == 0 && redir->hd_in == 0 && count > 1)
		redir->pipe_in = 1;
	if (redir->file_out == 0 && count > 1)
		redir->pipe_out = 1;
	return (0);
}


