/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:14:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/06 10:28:40 by llitovuo         ###   ########.fr       */
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
	if (update_pwd_cd(env, data) < 0)
		return (-1);
	return (0);
}

void	init_struct(t_cd *data)
{
	ft_bzero(data->expand, PATH_MAX);
	ft_bzero(data->home, PATH_MAX);
	ft_bzero(data->path, PATH_MAX);
	ft_strlcpy(data->path, "PWD=", PATH_MAX);
	ft_bzero(data->target, PATH_MAX);
	ft_bzero(data->cur_dir, PATH_MAX);
	data->ptr = NULL;
	data->split_path = NULL;
}

void	free_cd_struct(t_cd *data)
{
	ft_bzero(data->expand, PATH_MAX);
	ft_bzero(data->home, PATH_MAX);
	ft_bzero(data->path, PATH_MAX);
	ft_bzero(data->target, PATH_MAX);
	ft_bzero(data->cur_dir, PATH_MAX);
	data->ptr = NULL;
	data->split_path = NULL;
	free (data);
}

int	update_pwd_cd(t_vec *env, t_cd *data)
{
	int		index;
	char	*temp;

	index = find_index_of_env(env, "PWD");
	if (index < 0)
		return (-1);// err_mngmt
	ft_strlcat(data->path, data->target, PATH_MAX);
	temp = ft_strdup(data->path);
	if (!temp)
		return (-1);
	if (vec_replace_str(env, temp, index) < -1)
		return (-1);// err_mngmt
	return (0);
}
