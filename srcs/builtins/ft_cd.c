/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:27:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/04 15:24:57 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_cd(t_vec *env, t_vec *args)
{
	t_cd	*data;

	data = malloc (sizeof(t_cd));
	init_struct(data);
	if (copy_homedir(env, data) < 0 || get_cur_dir(env, data) < 0
		|| update_old_pwd(env, data) < -1)
		return (free_cd_struct(data), -1);
	if (args->len == 1)
		goto_home(env, data);
	if (args->len > 1 && (ft_strncmp(*(char **)vec_get(args, 1), "/", 2) == 0
			|| ft_strncmp(*(char **)vec_get(args, 1), "~", 2) == 0))
	{
		if (ft_strncmp(*(char **)vec_get(args, 1), "~", 2) == 0)
			goto_home(env, data);
		else
			goto_root(env);
		free_cd_struct(data);
		return (0);
	}
	if (args->len > 1 && goto_path(env, args, data) < 0)
		return (free_cd_struct(data), -1);
	free_cd_struct(data);
	return (0);
}

int	goto_path(t_vec *env, t_vec *args, t_cd *data)
{
	if (get_target_path(args, data) < 0)
		return (-1);
	if (access(data->target, F_OK) != 0)
	{
		error_triple_msg(3, "la_shell: cd: ", data->target, \
		": No such file or directory\n");
		return (-1);
	}
	if (access(data->target, X_OK) != 0)
	{
		error_triple_msg(3, "la_shell: cd: ", data->target, \
		": Permission denied\n");
		return (-1);
	}
	if (goto_dir(data, env) < 0)
		return (-1);
	return (0);
}

int	get_cur_dir(t_vec *env, t_cd *data)
{
	int		index;
	char	*temp;

	index = 0;
	index = find_index_of_env(env, "PWD");
	if (index < 0)
		return (-1);
	data->ptr = vec_get(env, index);
	temp = ft_substr(*(char **)data->ptr, 4, ft_strlen(*(char **)data->ptr));
	if (!temp)
		return (-1);
	ft_strlcpy(data->cur_dir, temp, PATH_MAX);
	free (temp);
	data->ptr = NULL;
	return (0);
}

int	get_target_path(t_vec *args, t_cd *data)
{
	char	*temp;

	temp = vec_get(args, 1);
	if (ft_strchr((*(char **)temp), '/') == *(char **)temp)
	{
		ft_strlcpy (data->target, *(char **)temp, PATH_MAX);
		return (0);
	}
	data->split_path = ft_split(*(char **)temp, '/');
	if (!data->split_path)
		return (-1);
	if (expand_relative_paths(data) < 0)
		return (-1);
	return (0);
}

int	expand_relative_paths(t_cd *data)
{
	int		i;
	int		parent_nbr;

	i = 0;
	parent_nbr = 0;
	ft_strlcpy(data->target, data->cur_dir, PATH_MAX);
	while (data->split_path[i])
	{
		if (ft_strncmp(data->split_path[i], "..", 3) == 0)
			get_parent(data, ++parent_nbr);
		else if (ft_strncmp(data->split_path[i], "~", 2) == 0)
			expand_home(data);
		else
		{
			if (data->target[ft_strlen(data->target) - 1] != '/')
				ft_strlcat(data->target, "/", PATH_MAX);
			if (ft_strlcat(data->target, data->split_path[i], PATH_MAX) < 0)
				return (-1);
			ft_strlcat(data->target, "/", PATH_MAX);
		}
		i++;
	}
	return (0);
}
