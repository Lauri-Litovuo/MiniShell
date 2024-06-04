/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:05:20 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/04 13:32:57 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	g_signal;

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

static int	validate_line(char **buf, char *hd_lim, t_redir *redir, t_vec *env)
{
	t_vec	temp;

	if (*buf == NULL)
		return (-1);
	if (ft_strncmp(*buf, hd_lim, ft_strlen(*buf) + 1) == 0)
	{
		redir->exit_code = 0;
		return (-1);
	}
	if (ft_strchr(*buf, '$') != NULL)
	{
		if (vec_new(&temp, 1, sizeof(char *)) < -1
			|| vec_push(&temp, &buf) < -1)
		{
			redir->exit_code = ERRO;
			return (-1);
		}
		if (expand_variables(redir->exit_code, env, &temp, 0) == -1 || *buf == NULL)
		{
			redir->exit_code = ERRO;
			return (ERRO);
		}
		*buf = *(char **)vec_get(&temp, 0);
	}
	return (0);
}

static int	heredoc_loop(t_redir *redir, int fd, t_vec *env)
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
			reset_fds(redir);
			return (EXIT_FAILURE);
		}
		if (validate_line(&buf, redir->hd_lim, redir, env) < 0)
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


static int	handle_heredoc(t_vec *rdrct, t_redir *redir, size_t pos, t_vec *env)
{
	int		fd;
	int		ret;

	ret = 0;
	while (pos < rdrct->len)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, pos), "<<", 3) == 0)
		{
			pos++;
			if (redir->hd_file)
				unlink (redir->hd_file);
			redir->hd_lim = *(char **)vec_get(rdrct, pos);
			redir->hd_file = get_hdfile_name(redir->hd_lim, (int)pos);
			fd = open (redir->hd_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
				return (unlink (redir->hd_file), -1);
			if (heredoc_loop(redir, fd, env) == 1)
				return (unlink (redir->hd_file), -1);
		}
		pos++;
	}
	return (ret);
}

int	check_for_heredoc(t_vec *rdrct, t_redir *redir, t_vec *env, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (ft_strncmp(*(char **)vec_get(rdrct, i), "<<", 3) == 0
			&& redir->hd_in == NO)
		{
			redir->hd_pos = i;
			redir->hd_in = YES;
			if (handle_heredoc(rdrct, redir, i, env) < 0)
			{
				redir->hd_in = ERRO;
				//free(redir);
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
