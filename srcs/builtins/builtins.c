/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:31:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 16:58:12 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	launch_builtin(t_vec *env, t_exec *exe)
{

	if (!cmd->memory)
		return (1);
	if (ft_strncmp(exe->cmd, "env", ft_strlen(exe->cmd) + 1) == 0)
		ft_env(env, cmd);
	else if (ft_strncmp(exe->cmd, "pwd", ft_strlen(exe->cmd) + 1) == 0)
		ft_pwd(env);
	else if (ft_strncmp(exe->cmd, "unset", ft_strlen(exe->cmd) + 1) == 0)
		ft_unset(env, cmd);
	else if (ft_strncmp(exe->cmd, "export", ft_strlen(exe->cmd) + 1) == 0)
		ft_export(env, cmd);
	else if (ft_strncmp(exe->cmd, "echo", ft_strlen(exe->cmd) + 1) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(exe->cmd, "cd", ft_strlen(exe->cmd) + 1) == 0)
		ft_cd(env, cmd);
	// else if (ft_strncmp(args, "exit", ft_strlen(args)) == 0)
	// 	ft_exit();
	else
		return (42);
	return (0);
}
