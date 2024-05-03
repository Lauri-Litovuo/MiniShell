/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:16:15 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/03 16:36:32 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	copy_homedir(t_vec *env, t_cd *data)
{
	int		index;

	index = find_index_of_env(env, "HOME");
	if (index < 0)
		return (NULL);
	ft_strlcpy(data->home, (*(char **)vec_get(env, index) + 5), PATH_MAX);
	if (!data->home)
		return (-1);
	return (0);
}

int	goto_home(t_vec *env, t_cd *data)
{
	ft_strlcat(data->path, data->home, PATH_MAX);
	if (!data->path)
		return (-1);
	if (access(data->home, F_OK) == 0)
	{
		if (chdir(data->home) != 0)
		{
			perror ("cd to ~ failed");
			return (-1);
		}
		if (update_pwd_env(env, data->path) < 0)
			return (-1);
	}
	else
		return (-1);
	return (0);
}

int	goto_root(t_vec *env)
{
	printf("going to root\n");
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

int	get_parent(t_cd *data)
{
	int		i;
	int		dir_count;
	int		len;

	dir_count = 0;
	i = 0;
	ft_bzero(data->target, PATH_MAX);
	while (*data->cur_dir != '\0')
	{
		if (*data->cur_dir == '/')
			dir_count++;
		i++;
	}
	while (i < dir_count)
	{
		if (data->cur_dir[len] == '/')
			i++;
		len++;
	}
	ft_strlcpy(data->target, data->cur_dir, len);
	if (!data->target)
		return (-1);
	return (0);
}


int	expand_home(t_cd *data)
{
	ft_bzero(data->target, PATH_MAX);
	ft_strlcpy(data->target, data->home, PATH_MAX);
	if (!data->target)
		return (-1);
	return (0);
}
