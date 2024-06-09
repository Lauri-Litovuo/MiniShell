/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:07:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/09 16:55:02 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_if_dir(char *cmd)
{
	DIR	*direc;

	if (!cmd)
		return (-1);
	direc = opendir(cmd);
	if (direc != NULL)
	{
		closedir(direc);
		return (DIRECTORY);
	}
	else if (errno == ENOTDIR)
		return (0);
	return (ERRO);
}

int	execute_cmd(t_exec *exe, t_shell *arg)
{
	char	**envp;

	envp = (char **)arg->env.memory;
	if (!exe->cmd || *exe->cmd == '\0')
		return (CMD_NOT_FOUND);
	if (check_if_dir(exe->cmd) == DIRECTORY)
		return (DIRECTORY);
	if (execve(exe->path, exe->cmd_argv, envp) == -1)
		return (execve_error(exe, strerror(errno), errno));
	return (-1);
}

int	 run_command(t_shell *arg, t_exec *exe)
{
	int	ret;
	
	ret = 0;
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
		if (ret != 0)
			error_triple_msg(2, exe->cmd, ": failed\n", NULL);
		close_fds_exit(arg, ret);
	}
	ret = execute_cmd(exe, arg);
	if (ret == DIRECTORY)
		execve_error(exe, "is a directory", 126);
	close_fds_exit(arg, ret);
	return (ret);
}
