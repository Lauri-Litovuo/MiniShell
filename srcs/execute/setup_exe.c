/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:43 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/12 13:25:49 by llitovuo         ###   ########.fr       */
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

int	split_vec(t_exec *exe, t_shell *arg, size_t i, size_t j)
{
	size_t	holder;
	char	**temp;
	size_t	count;
	char	*str;

	holder = arg[exe->pos].cmd.len;
	temp = NULL;
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
			temp = ft_split(*(char **)vec_get(&arg[exe->pos].cmd, i), ' ');
			if (!temp)
				return (-1);
			while (temp[count])
				count++;
			while (j < count)
			{
				str = ft_strdup(temp[j]);
				if (j == 0)
					vec_replace_str(&arg[exe->pos].cmd, str, i);
				else
					vec_insert(&arg[exe->pos].cmd, &str, i + j);
				j++;
			}
			i++;
		}
		holder = arg[exe->pos].cmd.len;
	}
	free_2d_array(temp);
	return (0);
}

void init_exec(t_exec *exe)
{
	exe->cmd_argv = NULL;
	exe->cmd = NULL;
	exe->path = NULL;
	exe->ret = 0;
	exe->pipe_fd = NULL;
	exe->pos = 0;
}

int	setup_exe(t_shell *arg)
{
	size_t	i;
	size_t	j;
	t_exec	**exe;

	i = 0;
	exe = (t_exec **) malloc ((arg->count + 1) * sizeof(t_exec *));
	if (!exe)
		return (-1);
	while (i < arg->count)
	{
		exe[i] = (t_exec *)malloc (sizeof(t_exec));
		if (!exe[i])
			return (-1);
		init_exec(exe[i]);
		exe[i]->pos = i;
		j = 0;
		if (arg->split_flag == 1)
			split_vec(exe[i], arg, 0, 0);
		printf("1\n");
		exe[i]->cmd_argv = malloc ((arg[i].cmd.len + 1) * sizeof(char *));
		if (!exe[i]->cmd_argv)
			return (-1);
		printf("2\n");
		while (j < arg[i].cmd.len)
		{
			exe[i]->cmd_argv[j] = ft_strdup(*(char **)vec_get(&arg[i].cmd, j));
			j++;
		}
		printf("3\n");
		exe[i]->cmd_argv[j] = NULL;
		if (arg[i].cmd.len != 0)
		{
			exe[i]->cmd = exe[i]->cmd_argv[0];
			exe[i]->path = get_exec_path(exe[i]->cmd, &arg->env);
			if (exe[i]->path == NULL)
				return (-1);
		}
		exe[i]->ret = 0;
		init_redir(&exe[i]->redir);
		if (arg[i].rdrct.len != 0)
		{
			if (open_files(&arg[i].rdrct, exe[i], arg) < 0)
				return (-1);
		}
		if (g_signal == 2)
			arg->exit_code = 1;
		if (exe[i]->pos > 0 && exe[i]->redir.file_in == NO && exe[i]->redir.hd_in == NO)
			exe[i]->redir.pipe_in = 1;
		if (exe[i]->redir.file_out == NO && arg->count > 1 && exe[i]->pos != arg->count - 1)
			exe[i]->redir.pipe_out = 1;
		i++;
	}
	exe[i] = NULL;
	arg->exe = exe;
	return (0);
}
