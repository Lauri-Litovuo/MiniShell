/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:31:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/22 15:43:10 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	launch_builtin(char *args, t_vec *env)
{
	if (ft_strncmp(args, "env", ft_strlen(args)) == 0)
		ft_env(env);
	else if (ft_strncmp(args, "pwd", ft_strlen(args)) == 0)
		ft_pwd();
	else if (ft_strncmp(args, "unset", ft_strlen(args)) == 0)
		ft_unset();
	// else if (ft_strncmp(args, "exit", ft_strlen(args)) == 0)
	// 	ft_exit();
	// else if (ft_strncmp(args, "echo", ft_strlen(args)) == 0)
	// 	ft_echo();
	// else if (ft_strncmp(args, "export", ft_strlen(args)) == 0)
	// 	ft_export();
	return (0);
}