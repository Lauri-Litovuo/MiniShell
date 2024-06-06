/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:43 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/06 17:34:56 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	g_signal;

int	init_redir(t_shell *arg, t_redir *redir)
{
	redir->fd_in = -1;
	redir->fd_out = -1;
	redir->hd_pos = -42;
	redir->re_pos = -42;
	redir->orig_fdin = dup(STDIN_FILENO);
	if (redir->orig_fdin == -1)
		return (perror("dup to in failed"), -1);
	redir->orig_fdout = dup(STDOUT_FILENO);
	if (redir->orig_fdout == -1)
		return (perror("dup to out failed"), -1);
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
	redir->exit_code = arg->exit_code;
	return (0);
}

int	split_vec(t_exec *exe, t_shell *arg, size_t i, size_t j)
{
	size_t	holder;
	char	**temp;
	size_t	count;
	char	*str;

	holder = arg[exe->pos].cmd.len;
	while (i < holder)
	{
		j = 0;
		count = 0;
		if (ft_strchr(*(char **)vec_get(&arg[exe->pos].cmd, i), ' ') == 0)
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
		}
		i++;
	}
	free(temp);
	return (0);
}

int	setup_exe(t_shell *arg)
{
	size_t	i;
	size_t	j;
	t_exec	**exe;
	t_exec	*sub_exe;

	i = 0;
	exe = malloc ((arg->count + 1) * sizeof(t_exec *));
	while (i < arg->count)
	{
		sub_exe = malloc (sizeof(t_exec));
		exe[i] = sub_exe;
		exe[i]->pos = i;
		j = 0;
		if (arg->split_flag == 1)
			split_vec(exe[i], arg, 0, 0);
		exe[i]->cmd_argv = malloc ((arg[i].cmd.len + 1) * sizeof(char *));
		while (j < arg[i].cmd.len)
		{
			exe[i]->cmd_argv[j] = ft_strdup(*(char **)vec_get(&arg[i].cmd, j));
			j++;
		}
		exe[i]->cmd_argv[j] = NULL;
		if (arg[i].cmd.len != 0)
		{
			exe[i]->cmd = exe[i]->cmd_argv[0];
			exe[i]->path = get_exec_path(exe[i]->cmd, &arg->env);
			if (exe[i]->path == NULL)
				return (-1);
		}
		exe[i]->ret = 0;
		exe[i]->exit_code = arg->exit_code;
		init_redir(arg, &exe[i]->redir);
		if (arg[i].rdrct.len != 0)
		{
			if (open_files(&arg[i].rdrct, exe[i], &arg->env) < 0)//
				return (-1);//
		}
		if (g_signal == 2)
			arg->exit_code = 1;
		if (sub_exe->pos > 0 && sub_exe->redir.file_in == NO && sub_exe->redir.hd_in == NO)
			sub_exe->redir.pipe_in = 1;
		if (sub_exe->redir.file_out == NO && arg->count > 1 && sub_exe->pos != arg->count - 1)
			sub_exe->redir.pipe_out = 1;
		i++;
	}
	exe[i] = NULL;
	arg->exe = exe;
	return (0);
}
