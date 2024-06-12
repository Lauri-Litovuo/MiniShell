/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:43 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/12 19:17:23 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	cleanup_exe(t_exec **exe, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		if (exe[i])
		{
			if (exe[i]->cmd_argv)
			{
				free_2d_array(exe[i]->cmd_argv);
			}
			free(exe[i]);
		}
		i++;
	}
	free(exe);
	return (-1);
}

void	setup_redirection(t_exec *exe, t_shell *arg, size_t i)
{
	init_redir(&exe->redir);
	if (arg[i].rdrct.len != 0)
	{
		if (open_files(&arg[i].rdrct, exe, arg) < 0)
		{
			cleanup_exe(arg->exe, arg->count);
			exit(-1);
		}
	}
	if (g_signal == 2)
		arg->exit_code = 1;
	if (exe->pos > 0 && exe->redir.file_in == NO && exe->redir.hd_in == NO)
		exe->redir.pipe_in = 1;
	if (exe->redir.file_out == NO && arg->count > 1
		&& exe->pos != arg->count - 1)
		exe->redir.pipe_out = 1;
}

int	setup_cmd_path(t_exec *exe, t_shell *arg, size_t i)
{
	if (arg[i].cmd.len != 0)
	{
		exe->cmd = exe->cmd_argv[0];
		exe->path = get_exec_path(exe->cmd, &arg->env);
		if (exe->path == NULL)
			return (-1);
	}
	exe->ret = 0;
	return (0);
}

int	setup_cmd_argv(t_exec *exe, t_shell *arg)
{
	size_t	j;

	exe->cmd_argv = (char **)malloc((arg->cmd.len + 1) * sizeof(char *));
	if (!exe->cmd_argv)
		return (-1);
	j = 0;
	while (j < arg->cmd.len)
	{
		exe->cmd_argv[j] = ft_strdup(*(char **)vec_get(&arg->cmd, j));
		if (!exe->cmd_argv[j])
		{
			free_2d_array(exe->cmd_argv);
			return (-1);
		}
		j++;
	}
	exe->cmd_argv[j] = NULL;
	return (0);
}

int	setup_exe(t_shell *arg)
{
	size_t	i;
	t_exec	**exe;

	exe = (t_exec **)malloc((arg->count + 1) * sizeof(t_exec *));
	if (!exe)
		return (cleanup_exe(NULL, 0));
	i = 0;
	while (i < arg->count)
	{
		exe[i] = (t_exec *)malloc(sizeof(t_exec));
		if (!exe[i] || init_exec(exe[i]) != 0)
			return (cleanup_exe(exe, i));
		exe[i]->pos = i;
		if (arg->split_flag == 1 && split_vec(exe[i], arg, 0, 0) == -1)
			return (cleanup_exe(exe, i + 1));
		if (setup_cmd_argv(exe[i], &arg[i]) == -1)
			return (cleanup_exe(exe, i + 1));
		if (setup_cmd_path(exe[i], arg, i) == -1)
			return (cleanup_exe(exe, i + 1));
		setup_redirection(exe[i], arg, i);
		i++;
	}
	exe[i] = NULL;
	arg->exe = exe;
	return (0);
}

/*
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
		exe[i]->cmd_argv = malloc ((arg[i].cmd.len + 1) * sizeof(char *));
		if (!exe[i]->cmd_argv)
			return (-1);
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
		init_redir(&exe[i]->redir);
		if (arg[i].rdrct.len != 0)
		{
			if (open_files(&arg[i].rdrct, exe[i], arg) < 0)
				return (-1);
		}
		if (g_signal == 2)
			arg->exit_code = 1;
		if (exe[i]->pos > 0 && exe[i]->redir.file_in == NO
			&& exe[i]->redir.hd_in == NO)
			exe[i]->redir.pipe_in = 1;
		if (exe[i]->redir.file_out == NO && arg->count > 1
			&& exe[i]->pos != arg->count - 1)
			exe[i]->redir.pipe_out = 1;
		i++;
	}
	exe[i] = NULL;
	arg->exe = exe;
	return (0);
}
*/
