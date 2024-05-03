/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:14:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/03 16:18:04 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	goto_dir(t_cd *data, t_vec *env)
{
	if (chdir(data->target) != 0)
	{
		perror ("cd to target failed");
		return (-1);
	}
	if (update_pwd_env(env, data->target) < 0)
		return (-1);
	return (0);
}

void	init_struct(t_cd *data)
{
	data = malloc (sizeof(t_cd));
	ft_bzero(data->expand, PATH_MAX);
	ft_bzero(data->home, PATH_MAX);
	ft_bzero(data->path, PATH_MAX);
	ft_strlcpy(data->path, "PWD=", PATH_MAX);
	ft_bzero(data->target, PATH_MAX);
	ft_bzero(data->cur_dir, PATH_MAX);
	data->ptr = NULL;
}

void	free_cd_struct(t_cd *data)
{
	free (data);
}
