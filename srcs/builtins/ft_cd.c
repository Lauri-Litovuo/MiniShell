/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:27:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/03 16:16:28 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_cd(t_vec *env, t_vec *args)
{
	t_cd	*data;

	init_struct(data);
	data->ptr = vec_get(args, 1);
	copy_homedir(env, &data);
	if (!data->home)
	{
		printf("cd failed"); //err_mngmt
		return (-1);
	}
	printf("args->len %zu\n", args->len);
	if (args->len == 1 || ft_strncmp(*(char **)data->ptr, "/", 2) == 0
		|| ft_strncmp(*(char **)data->ptr, "~", 2) == 0)
	{
		if (args->len == 1 || ft_strncmp(*(char **)data->ptr, "~", 2) == 0)
			goto_home(env, data->home);
		else
			goto_root(env);
		free_cd_struct(data);
		return (0);
	}
	if (goto_path(env, args, data->home) < 0)
		return (-1);
	free_cd_struct(data);
	return (0);
}

int	goto_path(t_vec *env, t_vec *args, t_cd *data)
{

	printf("going to path\n");
	get_cur_dir(env, data);
	printf("dir: %s\n", data->cur_dir);
	if (!data->cur_dir)
		return (-1);
	get_target_path(args, data);
	printf("target path: %s\n", data->target);
	if (!data->target)
		return (-1);
	else if (access(data->target, F_OK) == 0 && goto_dir(data, env) == 0)
		return (0);
	else
		return (-1);
	return (0);
}

char	*get_cur_dir(t_vec *env, t_cd *data)
{
	int		index;
	char	*cur_dir;
	char	*ptr;

	index = 0;
	index = find_index_of_env(env, "PWD");
	ptr = vec_get(env, index);
	if (index < 0)
		return (NULL);
	cur_dir = ft_substr(*(char **)ptr, 4, ft_strlen(*(char **)ptr));
	if (!cur_dir)
		return (NULL);
	return (cur_dir);
}

int	get_target_path(t_vec *args, t_cd *data)
{
	char	*temp;

	temp = vec_get(args, 1);
	if (ft_strchr((*(char **)temp), '/') == *(char **)temp)
		return (*(char **)temp);
	data->split_path = ft_split(*(char **)temp, '/');
	if (!data->split_path)
		return (NULL);
	if (expand_relative_paths(data) < 0)
		return (-1);
	return (0);
}


int	expand_relative_paths(t_cd *data)
{
	int		i;

	i = 0;
	ft_strlcpy(data->target, data->cur_dir, PATH_MAX);
	ft_strlcat(data->target, "/", PATH_MAX);
	if (!data->target)
		return (-1);
	while (data->split_path[i])
	{
		printf("yoyoyo%s\n", data->split_path[i]); //
		if (ft_strncmp(data->split_path[i], "..", 3) == 0)
			get_parent(data);
		else if (ft_strncmp(data->split_path[i], "~", 2) == 0)
			expand_home(data);
		else
		{
			ft_strlcat(data->target, data->split_path[i], PATH_MAX);
			if (!data->target)
				return (-1);
		}
		i++;
	}
	return (0);
}
