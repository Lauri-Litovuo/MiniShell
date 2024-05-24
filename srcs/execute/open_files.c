/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:51:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 10:07:16 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"



int	open_infiles(t_vec *rdrct, t_redir *redir, int pos)
{
	char	*filename;
	int		temp;

	temp = -42;
	filename = *(char **)vec_get(rdrct, pos);
	temp = open(filename, O_RDONLY);
	while (pos++ < rdrct->len && temp != -1)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, pos), "<", 2) == 0)
		{
			redir->re_pos = pos;
			pos++;
			filename = *(char **)vec_get(rdrct, pos);
			temp = open(filename, O_RDONLY);
		}
	}
	redir->infile = filename; // remove if uneccessary
	if (redir->re_pos > redir->hd_pos)
		redir->fd_in = temp;
	redir->file_in = ERR;
	if (temp == ERR)
		return (write_file_error(filename, strerror(errno)), -1); //check how errno works
	redir->file_in = YES;
	return (0);
}

int	get_fdout(t_vec *rdrct, t_redir *redir, int pos)
{
	redir->i = -42;
	redir->outfile = *(char **)vec_get(rdrct, pos++);
	if (ft_strncmp(*(char **)vec_get(rdrct, pos), ">>", 3))
		redir->i = open (redir->outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		redir->i = open (redir->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	while (pos++ < rdrct->len && redir->i != -1)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, pos), ">>", 3))
		{
			redir->outfile = *(char **)vec_get(rdrct, pos++);
			redir->i = open(redir->outfile, O_RDWR | O_APPEND | O_CREAT, 0644);
		}
		else if (ft_strncmp(*(char **)vec_get(rdrct, pos++), ">", 2) == 0)
		{
			redir->outfile = *(char **)vec_get(rdrct, pos);
			redir->i = open(redir->outfile, O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
	}
	redir->fd_out = redir->i;
	redir->file_out = ERR;
	if (redir->i == ERR)
		return (write_file_error(redir->outfile, strerror(errno)), -1);
	redir->file_out = YES;
	return (0);
}


int	setup_and_open_files(t_vec *rdrct, t_redir *redir)
{
	int	i;

	i = 0;
	while (i < rdrct->len)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, i), "<", 2) == 0
			&& redir->file_in == NO)
		{
			redir->re_pos = i;
			redir->file_in = open_infiles(rdrct, redir, i++);
		}
		else if (redir->file_out == NO
			&& ((ft_strncmp(*(char **)vec_get(rdrct, i), ">", 2) == 0)
				|| ft_strncmp(*(char **)vec_get(rdrct, i), ">>", 3) == 0))
			redir->file_out = open_outfile(rdrct, redir, i);
		i++;
	}
	return (0);
}

int	open_files(t_vec *rdrct, t_redir *redir, t_vec *env)
{
	if (rdrct->len != 0)
	{
		if (check_for_heredoc(rdrct, redir, env) < 0)
			return (ft_fprintf(2, "minishell :heredoc failed."), -1);
		if (setup_and_open_files(rdrct, redir) < 0)
			return (-1);
	}
	if (redir->file_in == 0 && redir->hd_in == 0)
		redir->pipe_in = 1;
	if (redir->file_out == 0)
		redir->pipe_out = 1;
	return (0);
}


