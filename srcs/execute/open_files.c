/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:51:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/06 16:51:28 by aneitenb         ###   ########.fr       */
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
	if (fd == -1)
		file_error(filename, strerror(errno));
	while (fd != -1 && ++pos < rdrct->len)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, pos), "<", 2) == 0)
		{
			close(fd);
			redir->re_pos = pos;
			filename = *(char **)vec_get(rdrct, ++pos);
			fd = open(filename, O_RDONLY);
			if (fd == -1)
				file_error(filename, strerror(errno));
		}
	}
	redir->infile = filename;
	if (redir->re_pos > redir->hd_pos)
		redir->fd_in = fd;
	redir->file_in = ERRO;
	if (fd == ERRO)
		return (-1);
	redir->file_in = YES;
	return (redir->file_in);
}

static int	loop_for_open(t_vec *rdrct, t_redir *redir, size_t *pos)
{
	if (ft_strncmp(">", *(char **)vec_get(rdrct, *pos), 2) == 0)
	{
		close(redir->i);
		redir->outfile = *(char **)vec_get(rdrct, ++(*pos));
		redir->i = open(redir->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (redir->i == -1)
		{
			redir->fd_out = redir->i;
			redir->file_out = ERRO;
			return (file_error(redir->outfile, strerror(errno)), -1);
		}
	}
	else if (ft_strncmp(">>", *(char **)vec_get(rdrct, *pos), 3) == 0)
	{
		close (redir->i);
		redir->outfile = *(char **)vec_get(rdrct, ++(*pos));
		redir->i = open(redir->outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (redir->i == -1)
		{
			redir->fd_out = redir->i;
			redir->file_out = ERRO;
			return (file_error(redir->outfile, strerror(errno)), -1);
		}
	}
	return (0);
}


static int	open_outfiles(t_vec *rdrct, t_redir *redir, size_t pos)
{
	redir->i = -42;
	redir->outfile = *(char **)vec_get(rdrct, pos + 1);
	if (ft_strncmp(">", *(char **)vec_get(rdrct, pos), 2) == 0)
		redir->i = open (redir->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else
		redir->i = open (redir->outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (redir->i == -1)
	{
		redir->fd_out = redir->i;
		redir->file_out = ERRO;
		return (file_error(redir->outfile, strerror(errno)), -1);
	}
	pos++;
	while (pos < rdrct->len && redir->i != -1)
	{
		if (loop_for_open(rdrct, redir, &pos) < 0)
			return (-1);
		pos++;
	}
	redir->fd_out = redir->i;
	redir->file_out = ERRO;
	if (redir->i == ERRO)
		return (file_error(redir->outfile, strerror(errno)), -1);
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

int	open_files(t_vec *rdrct, t_exec *exe, t_shell *arg)
{
	t_redir	*redir;

	redir = &exe->redir;
	if (rdrct->len != 0)
	{
		if (check_for_heredoc(rdrct, redir, arg, rdrct->len) < 0)
			return (-1);
		if (setup_and_open_files(rdrct, redir) < 0)
			return (-1);
	}
	return (0);
}
