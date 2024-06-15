/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:31:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/15 21:19:20 by llitovuo         ###   ########.fr       */
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
		ret = ft_env(env, exe);
	else if (ft_strncmp(exe->cmd, "pwd", 4) == 0)
		ret = ft_pwd(arg);
	else if (ft_strncmp(exe->cmd, "unset", 6) == 0)
		ret = ft_unset(env, arg->in[exe->pos]->cmd);
	else if (ft_strncmp(exe->cmd, "export", 7) == 0)
		ret = ft_export(env, arg->in[exe->pos]->cmd);
	else if (ft_strncmp(exe->cmd, "echo", 5) == 0)
		ret = ft_echo(arg->in[exe->pos]->cmd);
	else if (ft_strncmp(exe->cmd, "cd", 3) == 0)
		ret = ft_cd(env, arg->in[exe->pos]->cmd, arg);
	else if (ft_strncmp(exe->cmd, "exit", 5) == 0)
		ret = ft_exit(exe, arg);
	return (ret);
}
