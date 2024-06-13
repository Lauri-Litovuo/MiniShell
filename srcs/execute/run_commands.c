/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:07:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/13 14:32:01 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_if_dir(char *cmd)
{
	DIR	*direc;

	if (!cmd || ft_strchr(cmd, '/') == NULL)
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

void	handle_child_assignments(t_exec *exe, t_shell *arg)
{
	size_t	i;

	i = 0;
	set_pipe_fds(exe, arg);
	set_fds(&exe->redir);
	while (i < arg->count && i != exe->pos)
	{
		close_fds(arg->exe[i]);
		i++;
	}
	close (arg->orig_fd[0]);
	close (arg->orig_fd[1]);
}

int	run_command(t_shell *arg, t_exec *exe)
{
	int	ret;

	if (!exe || !exe->cmd || !exe->cmd_argv
		|| check_files_and_fd(&exe->redir) == ERRO)
		exit(1);
	if (exe->cmd[0] == '\0')
		exit (0);
	handle_child_assignments(exe, arg);
	ret = 0;
	if (isit_builtin(exe->cmd, exe->pos) == INT_MIN)
	{
		ret = launch_builtin(&arg->env, exe, arg);
		if (ret != 0)
			error_triple_msg(2, exe->cmd, ": failed\n", NULL);
		close_fds_exit(arg, ret);
	}
	ret = execute_cmd(exe, arg);
	if (ret == DIRECTORY)
		ret = execve_error(exe, "is a directory", 126);
	close_fds_exit(arg, ret);
	return (ret);
}
