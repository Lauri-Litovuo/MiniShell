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


int	get_fdin(t_vec *rdrct, t_vec *fd_in, int i)
{
	char	*filename;
	int		temp;

	if (i < rdrct->len)
	{
		i++;
		filename = *(char **)vec_get(rdrct, i);
		temp = open(filename, O_RDONLY);
		if (temp == -1)
		{
			write (2, "minishell: ", 7);
			perror (filename);
			return (-1);
		}
	}
	vec_push(&fd_in, temp);
	return (0);
}

int	get_fdout(t_vec *rdrct, t_vec *fd_out, int i)
{
	char	*filename;
	int		temp;


	while (i < rdrct->len)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, i), ">", 2) == 0)
		{
			i++;
			filename = *(char **)vec_get(rdrct, i);
			temp = open (filename, O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (temp < 0)
			{
				write (2, "minishell: ", 7);
				perror(filename);
				return (-1);
			}
		}
		i++;
	}
	vec_push(&fd_out, temp);
	return (0);
}

int	check_redirs(t_vec *rdrct, t_redir *redir)
{
	int	i;

	i = 0;
	while (i < rdrct->len)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, i), "<", 2) == 0)
			redir->file_in = get_fdin(rdrct, redir, i);
		else if (ft_strncmp(*(char **)vec_get(rdrct, i), ">", 2) == 0)
			redir->file_out = get_fdout(rdrct, redir, i);
		else if (ft_strncmp(*(char **)vec_get(rdrct, i), ">>", 3) == 0)
			redir->hd_out = handle_heredoc_out(rdrct, redir, i);
		else if (ft_strncmp(*(char **)vec_get(rdrct, i), "<<", 3) == 0)
			redir->hd_in = handle_heredoc_in(rdrct, redir, i);
		i++;
	}
	return (0);
}

int	open_files(t_vec *rdrct, t_redir *redir, t_exec *pre)
{
	if (rdrct->len == 0 && pre != NULL)
	{
		if (pre->redir.pipe_out == 0)
	}
	check_redirs(rdrct, redir);
	if (redir->file_in == 0 && redir->hd_in == 0)
		redir->pipe_in = 1;
	if (redir->file_out == 0 && redir->hd_out == 0)
		redir->pipe_out = 1;
}
