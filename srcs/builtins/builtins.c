/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:31:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/17 10:37:49 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	launch_builtin(t_vec *env, t_vec *cmd, t_redir *redir)
{
	char	**arg_strs;

	if (!cmd->memory)
		return (1);
	arg_strs = (char **)cmd->memory;
	if (ft_strncmp(arg_strs[0], "env", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_env(env, cmd);
	else if (ft_strncmp(arg_strs[0], "pwd", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_pwd(env);
	else if (ft_strncmp(arg_strs[0], "unset", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_unset(env, cmd);
	else if (ft_strncmp(arg_strs[0], "export", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_export(env, cmd);
	else if (ft_strncmp(arg_strs[0], "echo", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(arg_strs[0], "cd", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_cd(env, cmd);
	// else if (ft_strncmp(args, "exit", ft_strlen(args)) == 0)
	// 	ft_exit();
	return (0);
}
