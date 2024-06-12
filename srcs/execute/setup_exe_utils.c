/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:50:50 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/12 19:02:07 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	init_redir(t_redir *redir)
{
	redir->fd_in = -1;
	redir->fd_out = -1;
	redir->hd_pos = -42;
	redir->re_pos = -42;
	redir->pipe_out = NO;
	redir->pipe_in = NO;
	redir->file_in = NO;
	redir->file_out = NO;
	redir->hd_in = NO;
	redir->infile = NULL;
	redir->outfile = NULL;
	redir->hd_lim = NULL;
	redir->hd_file = NULL;
	redir->i = -42;
	return (0);
}

int	init_exec(t_exec *exe)
{
	exe->cmd_argv = NULL;
	exe->cmd = NULL;
	exe->path = NULL;
	exe->ret = 0;
	exe->pipe_fd = NULL;
	exe->pos = 0;
	return (0);
}

int	split_insert(t_exec *exe, t_shell *arg, size_t i)
{
	char	**temp;
	size_t	count;
	size_t	j;
	char	*str;

	temp = NULL;
	temp = ft_split(*(char **)vec_get(&arg[exe->pos].cmd, i), ' ');
	if (!temp)
		return (-1);
	count = 0;
	while (temp[count])
		count++;
	j = 0;
	while (j < count)
	{
		str = ft_strdup(temp[j]);
		if (j == 0)
			vec_replace_str(&arg[exe->pos].cmd, str, i);
		else
			vec_insert(&arg[exe->pos].cmd, &str, i + j);
		j++;
	}
	free_2d_array(temp);
	return (0);
}

int	split_vec(t_exec *exe, t_shell *arg, size_t i, size_t j)
{
	size_t	holder;
	size_t	count;
	char	*str;

	holder = arg[exe->pos].cmd.len;
	while (i < holder)
	{
		j = 0;
		count = 0;
		if ((*(char **)vec_get(&arg[exe->pos].cmd, i))[0] == '\0')
		{
			vec_remove_str(&arg[exe->pos].cmd, i);
			i++;
		}
		else if (ft_strchr(*(char **)vec_get(&arg[exe->pos].cmd, i), ' ') == 0)
			i++;
		else
		{
			if (split_insert(exe, arg, i) < 0)
				return (-1);
			i++;
		}
		holder = arg[exe->pos].cmd.len;
	}
	return (0);
}