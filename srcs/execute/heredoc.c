/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:05:20 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/16 10:55:46 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*get_hdfile_name(char *str, int i)
{
	char	*ret;
	char	*temp;
	char	*new;

	temp = ft_itoa(i);
	ret = ft_strdup(str);
	if (!ret)
		return (NULL);
	new = ft_strjoin(ret, temp);
	free(temp);
	free(ret);
	if (!new)
		return (NULL);
	return (new);
}

static int	validate_line(char **buf, char *hd_lim, t_shell *arg)
{
	t_vec	temp;

	if (*buf == NULL)
		return (-1);
	if (ft_strncmp(*buf, hd_lim, ft_strlen(*buf) + 1) == 0)
		return (-1);
	if (ft_strchr(*buf, '$') != NULL)
	{
		if (vec_new(&temp, 1, sizeof(char *)) < -1
			|| vec_push(&temp, &buf) < -1)
			return (-1);
		if (expand_variables(arg, &temp, 0) == -1 || *buf == NULL)
			return (-1);
		*buf = *(char **)vec_get(&temp, 0);
	}
	return (0);
}

static int	heredoc_loop(t_redir *redir, int fd, t_shell *arg)
{
	char	*buf;

	buf = NULL;
	set_fds(redir);
	while (1)
	{
		signals_heredoc();
		buf = readline("> ");
		signals_default();
		if (g_signal == 2)
		{
			close(fd);
			reset_fds(arg->orig_fd);
			return (-1);
		}
		if (validate_line(&buf, redir->hd_lim, arg) < 0)
			break ;
		ft_putstr_fd(buf, fd);
		free(buf);
		ft_putstr_fd("\n", fd);
	}
	if (buf)
		free(buf);
	close(fd);
	return (0);
}

static int	handle_heredoc(t_vec *rdrct, \
t_redir *redir, size_t pos, t_shell *arg)
{
	int		fd;

	redir->hd_pos = pos;
	redir->hd_in = YES;
	while (pos < rdrct->len)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, pos), "<<", 3) == 0)
		{
			pos++;
			if (redir->hd_file)
				unlink (redir->hd_file);
			if (redir->hd_file)
				free (redir->hd_file);
			redir->hd_lim = *(char **)vec_get(rdrct, pos);
			redir->hd_file = get_hdfile_name(redir->hd_lim, (int)pos);
			fd = open (redir->hd_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return (unlink (redir->hd_file), -1);
			if (heredoc_loop(redir, fd, arg) < 0)
				return (heredoc_fails(redir, fd));
		}
		pos++;
	}
	return (0);
}

int	check_for_heredoc(t_vec *rdrct, t_redir *redir, \
t_shell *arg, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, i), "<<", 3) == 0
			&& redir->hd_in == NO)
		{
			if (handle_heredoc(rdrct, redir, i, arg) < 0)
			{
				redir->hd_in = ERRO;
				return (-1);
			}
		}
		i++;
	}
	if (redir->hd_in == YES && redir->hd_pos > redir->re_pos)
	{
		if (redir->re_pos != -42)
			close (redir->fd_in);
		redir->fd_in = open (redir->hd_file, O_RDONLY);
		if (redir->fd_in < 0)
			unlink(redir->hd_file);
	}
	return (0);
}
