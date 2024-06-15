/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:27:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/15 23:45:24 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_cd(t_vec *env, t_vec *args, t_shell *arg)
{
	t_cd	*data;

	data = malloc (sizeof(t_cd));
	init_struct(data);
	if (copy_homedir(env, data, arg) < 0 || get_cur_dir(env, data, arg) < 0
		|| update_old_pwd(env, data) < -1)
		return (free_cd_struct(data), 1);
	if (args->len == 1)
		goto_home(env, data, arg, 0);
	else if (args->len > 1
		&& (ft_strncmp(*(char **)vec_get(args, 1), "/", 2) == 0
			|| ft_strncmp(*(char **)vec_get(args, 1), "~", 2) == 0
			|| ft_strncmp(*(char **)vec_get(args, 1), ".", 2) == 0))
	{
		if (ft_strncmp(*(char **)vec_get(args, 1), "~", 2) == 0)
			goto_home(env, data, arg, YES);
		else if (ft_strncmp(*(char **)vec_get(args, 1), "/", 2) == 0)
			goto_root(env, data, arg);
		free_cd_struct(data);
		return (0);
	}
	else if (args->len > 1 && goto_path(env, args, data, arg) < 0)
		return (free_cd_struct(data), 1);
	free_cd_struct(data);
	return (0);
}

int	goto_path(t_vec *env, t_vec *args, t_cd *data, t_shell *arg)
{
	if (get_target_path(args, data, arg) < 0)
		return (-1);
	if (check_if_dir(data->target) == 0)
	{
		error_triple_msg(3, "la_shell: cd: ", *(char **)vec_get(args, 1), \
		": Not a directory\n");
		return (-1);
	}
	if (access(data->target, F_OK) != 0)
	{
		error_triple_msg(3, "la_shell: cd: ", *(char **)vec_get(args, 1), \
		": No such file or directory\n");
		return (-1);
	}
	if (access(data->target, X_OK) != 0)
	{
		error_triple_msg(3, "la_shell: cd: ", *(char **)vec_get(args, 1), \
		": Permission denied\n");
		return (-1);
	}
	if (goto_dir(data, env, arg) < 0)
		return (-1);
	return (0);
}

int	get_cur_dir(t_vec *env, t_cd *data, t_shell *arg)
{
	(void)env;
	ft_strlcpy(data->cur_dir, arg->pwd, PATH_MAX);
	return (0);
}

int	get_target_path(t_vec *args, t_cd *data, t_shell *arg)
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
	if (expand_relative_paths(data, arg, 0) < 0)
		return (-1);
	return (0);
}

int	expand_relative_paths(t_cd *data, t_shell *arg, int i)
{
	int		parent_nbr;

	parent_nbr = 0;
	ft_strlcpy(data->target, data->cur_dir, PATH_MAX);
	while (data->split_path[i])
	{
		if (ft_strncmp(data->split_path[i], "..", 3) == 0)
			get_parent(data, ++parent_nbr);
		else if (ft_strncmp(data->split_path[i], "~", 2) == 0)
		{
			if (expand_home(data, &arg->env) < 0)
				return (-1);
		}
		else if (ft_strncmp(data->split_path[i], ".", 1) == 0)
		{
			if (expand_cur_dir(data, data->split_path[i]) < 0)
				return (-1);
		}
		else
			if (add_to_target(data, i) < 0)
				return (-1);
		i++;
	}
	return (0);
}
