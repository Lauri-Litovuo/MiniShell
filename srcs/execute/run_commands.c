/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:07:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 12:01:52 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	child_execute(t_shell *arg, t_exec *exe, int *fd, int i)
{
	int	ret;

	ret = 0;
	ret = do_redirects(arg, &exe->redir, fd);
	if (ret < 0)
		close_and_exit();
	close_fds(&exe->redir);
	if (isit_child_builtin(exe->cmds[i]) == 1)
	{
		ret = launch_builtin(&arg->env, &arg->cmd, &exe->redir);
		if (ret < 0)
			return (ret);
	}
	else
		if (execve(exe->paths[0], &exe->cmds[0][0], NULL) == -1)
			perror(exe->cmds[0][0]);
	else
	{
		close_and_exit();
	}
}

int	first_run(t_exec *exe, t_vec *env)
{
	t_exec	exe;
	int		pid;

}



int	middle_run(t_exec *exe, t_vec *env)
{
	
}

int	last_run(t_exec *exe, t_vec *env)
{
	
}

