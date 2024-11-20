/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:34:18 by llitovuo          #+#    #+#             */
/*   Updated: 2024/11/20 14:16:23 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	add_to_target(t_cd *data, int i)
{
	if (data->target[ft_strlen(data->target) - 1] != '/')
		ft_strlcat(data->target, "/", PATH_MAX);
	if ((int)ft_strlcat(data->target, data->split_path[i], PATH_MAX) < 0)
		return (-1);
	ft_strlcat(data->target, "/", PATH_MAX);
	return (0);
}

void	home_error(t_cd *data, int i)
{
	if (i == 2)
	{
		ft_putstr_fd("la_shell: cd: ", STDERR_FILENO);
		ft_putstr_fd(data->home, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
}
