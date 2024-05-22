/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:05:20 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/21 12:09:53 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	*get_hdfile_name(char *str, int i)
{
	char	*ret;
	char	*temp;

	ret = ft_strdup(".");
	if (!ret)
		return (NULL);
	temp = ft_itoa(i);
	if (ft_strjoin(ret, temp) == NULL)
		return (NULL);
	free (temp);
	if (ft_strjoin(ret, str) == NULL)
		return (NULL);
	return (ret);
}

int	validate_line(char **buf, char *hd_lim, int *ret, t_vec *env)
{
	t_vec	temp;
	int		check;

	if (buf == NULL)
	{
		*ret = -1;
		return (-1);
	}
	if (ft_strncmp(buf, hd_lim, ft_strlen(buf) + 1) == '\n')
	{
		*ret = 0;
		return (-1);
	}
	if (ft_strchr(buf, '$') != NULL)
	{
		if (vec_new(&temp, 1, sizeof(char *)) < -1
			|| vec_push(&temp, &buf) < -1)
		{
			*ret = -1;
			return (-1);
		}
		if (expand_variables(&env, &temp, 0) != -1)
		{
			if (*buf == NULL)
			{
				*ret = -1;
				return (-1);
			}
		}
	}
	return (0);
}


int	handle_heredoc(t_vec *rdrct, t_redir *redir, int i, t_vec *env)
{
	int		fd;
	char	*buf;
	int		ret;

	redir->hd_lim = *(char **)vec_get(rdrct, i + 1);
	redir->hd_file = get_hdfile_name(redir->hd_lim, i);
	redir->hd_pos = i;
	fd = open (redir->hd_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd < 0)
		return (-1); //
	while (1)
	{
		printf(">");
		buf = get_next_line(STDIN_FILENO);
		if (buf == NULL)
			exit (EXIT_FAILURE);
		if (validate_line(&buf, redir->hd_lim, &ret, &env) < 0)
			break ;
		ft_putstr_fd(buf, fd);
		free(buf);
	}
	free(buf);
	close (fd);
	redir->fd_in = open (redir->hd_file, O_RDONLY);
	if (redir->fd_in < 0)
		unlink(redir->hd_file);
	return (ret);
}

check_for_heredoc(rdrct, redir, env)
{
	
}
