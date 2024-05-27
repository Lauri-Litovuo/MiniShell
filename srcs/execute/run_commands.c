/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:07:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/27 13:04:19 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	execute_cmd(t_exec *exe, t_shell *arg)
{
	if (!exe->cmd || *exe->cmd == '\0')
		return (42);
	if (check_if_dir(exe->cmd) == YES)
		return (42);
	execve(exe->path, exe->cmd_argv, &arg->env);
	ft_fprintf(2, "Minishell: execve: failed!");
	exit (1);
}

int	run_command(t_shell *arg, t_exec *exe)
{
	int	ret;

	if (!exe || !exe->cmd || !exe->cmd_argv)
		exit(1); //
	if (check_files_and_fd(exe->redir) == ERRO)
		exit (1);//
	set_pipe_fds(exe, arg);
	set_fds(exe->redir);
	close_other_pipe_fds(arg, exe, exe->pos);
	ret = launch_builtin(env, exe);
	if (ret!= 42)
		exit_child(arg, ret);
	ret = execute_cmd(exe, arg);
	if (ret != 42)
		exit_child(arg, ret);
	exit_child(arg, ret);
	return(ret);
}