/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:31:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/27 13:20:45 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	launch_builtin(t_vec *env, t_exec *exe, t_shell *arg)
{
	int	ret;

	ret = -42;
	if (!exe->cmd)
		return (ret);
	if (ft_strncmp(exe->cmd, "env", 4) == 0)
		ft_env(env, exe);
	else if (ft_strncmp(exe->cmd, "pwd", 4) == 0)
		ft_pwd(env);
	else if (ft_strncmp(exe->cmd, "unset", 6) == 0)
		ft_unset(env, &arg[exe->pos].cmd);
	else if (ft_strncmp(exe->cmd, "export", 7) == 0)
		ft_export(env, &arg[exe->pos].cmd);
	else if (ft_strncmp(exe->cmd, "echo", 5) == 0)
		ft_echo(&arg[exe->pos].cmd);
	else if (ft_strncmp(exe->cmd, "cd", 3) == 0)
		ft_cd(env, &arg[exe->pos].cmd);
	else if (ft_strncmp(exe->cmd, "exit", 5) == 0)
	 	ft_exit(exe, arg);
	return (ret);
}
