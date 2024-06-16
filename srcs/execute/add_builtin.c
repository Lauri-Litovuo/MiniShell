/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:00:55 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/16 12:21:28 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	isit_builtin(char *cmd, int pos)
{
	if (!cmd)
		return (-1);
	if (ft_strncmp(cmd, "env", ft_strlen(cmd) + 1) == 0
		|| ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1) == 0
		|| ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1) == 0
		|| ft_strncmp(cmd, "export", ft_strlen(cmd) + 1) == 0
		|| ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1) == 0
		|| ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1) == 0
		|| ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1) == 0)
		return (INT_MIN);
	else
		return (pos);
}
