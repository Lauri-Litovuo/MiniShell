/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:00:55 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/27 17:36:06 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	isit_builtin(char *cmd, int pos)
{
	if (!cmd)
		exit (1);
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

int	add_builtin(t_vec *paths, char *cmd)
{
	char	*temp;

	if (cmd)
	{
		temp = ft_strdup(cmd);
		if (vec_push(paths, &temp) < 0)
			exit (1);
		return (0);
	}
	return (-1);
}
