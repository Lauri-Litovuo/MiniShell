/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:16:15 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/11 10:05:21 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	copy_homedir(t_vec *env, t_cd *data)
{
	int		index;

	index = find_index_of_env(env, "HOME");
	if (index < 0)
		return (-1);
	ft_strlcpy(data->home, (*(char **)vec_get(env, index) + 5), PATH_MAX);
	return (0);
}

int	goto_home(t_vec *env, t_cd *data)
{
	ft_strlcat(data->path, data->home, PATH_MAX);
	if (access(data->home, F_OK) == 0)
	{
		if (chdir(data->home) != 0)
		{
			perror ("cd to ~ failed");
			return (-1);
		}
		if (update_pwd_cd(env, data) < 0)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	goto_root(t_vec *env)
{
	if (access("/", F_OK) == 0)
	{
		if (chdir("/") != 0)
		{
			perror ("cd to / failed");
			return (-1);
		}
		if (update_pwd_env(env, "PWD=/") < 0)
			return (-1);
	}
	return (0);
}

int	get_parent(t_cd *data, int parent_nbr)
{
	int		i;
	char	**temp;
	int		len;

	i = 0;
	len = 0;
	temp = ft_split(data->cur_dir, '/');
	if (!temp)
		return (-1);
	while (temp[len] != NULL)
		len++;
	ft_strlcpy(data->target, "/", PATH_MAX);
	if (len <= 1 || len <= parent_nbr)
	{
		free_2d_array(temp);
		return (0);
	}
	while (i < len - parent_nbr)
	{
		ft_strlcat(data->target, temp[i], PATH_MAX);
		ft_strlcat(data->target, "/", PATH_MAX);
		i++;
	}
	free_2d_array(temp);
	return (0);
}

int	expand_home(t_cd *data)
{
	ft_bzero(data->target, PATH_MAX);
	ft_strlcpy(data->target, data->home, PATH_MAX);
	ft_strlcat(data->target, "/", PATH_MAX);
	return (0);
}

