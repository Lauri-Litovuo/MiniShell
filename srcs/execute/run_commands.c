/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:07:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/29 12:04:49 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	check_if_dir(char *cmd)
{
	DIR	*direc;

	direc = opendir(cmd);
	if (direc != NULL)
	{
		closedir (direc);
		return (YES);
	}
	if (errno == ENOTDIR)
		return (NO);
	return (ERRO);
}

int	execute_cmd(t_exec *exe, t_shell *arg)
{
	char	**envp;

	envp = (char **)arg->env.memory;
	if (!exe->cmd || *exe->cmd == '\0')
		return (-42);
	if (check_if_dir(exe->cmd) == YES)
		return (DIRECTORY);
	if (execve(exe->path, exe->cmd_argv, envp) == -1)
		perror(exe->cmd);
	printf("execve failed\n"); //
	return (-1);
}

int	run_command(t_shell *arg, t_exec *exe)
{
	int	ret;

	if (!exe || !exe->cmd || !exe->cmd_argv)
		exit(1);
	if (check_files_and_fd(&exe->redir) == ERRO)
		exit (1);
	set_pipe_fds(exe, arg);
	set_fds(&exe->redir);
	close_fds(exe, NO);
	if (isit_builtin(exe->cmd, exe->pos) == INT_MIN)
	{
		ret = launch_builtin(&arg->env, exe, arg);
		close_fds_exit(arg, ret);
	}
	ret = execute_cmd(exe, arg);
	return (ret);
}
