/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:27:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/02 16:06:04 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// make function that checks if path is accessible
// take path to change pwd
// 


int	ft_cd(t_vec *env, t_vec *args)
{
	char	*ptr;
	char	*home;

	ptr = vec_get(args, 1);
	home = copy_homedir(env);
	if (!home)
	{
		printf("cd failed"); //err_mngmt
		return (-1);
	}
	if (args->len == 1 || ft_strncmp(*(char **)ptr, "/", 2)
		|| ft_strncmp(*(char **)ptr, "~", 2))
	{
		if (args->len == 1 || ft_strncmp(*(char **)ptr, "~", 2))
			goto_home(env, home);
		else
			goto_root(env);
		free (home);
		return (0);
	}
	if (goto_path(env, args, home) < 0)
		return (-1);
	free (home);
	return (0);
}

int	goto_path(t_vec *env, t_vec *args, char *home)
{
	char	*cur_dir;
	char	*target;

	cur_dir = NULL;
	get_cur_dir(env, cur_dir);
	if (!cur_dir)
		return (-1);
	target = get_target_path(args, cur_dir, home);
	if (!target)
	{
		free(cur_dir);
		return (-1);
	}
	else if (access(target, F_OK) == 0 && goto_dir(target, env) == 0)
	{
		free(target);
		free(cur_dir);
		return (0);
	}
	else
	{
		free(target);
		free(cur_dir);
		return (-1);
	}
	return (0);
}

void	get_cur_dir(t_vec *env, char *cur_dir)
{
	int	index;

	index = find_index_of_env(env, "PWD");
	if (index < 0)
		return ;
	cur_dir = ft_strdup(*(char **)vec_get(env, index) + 5);
	if (!cur_dir)
		return ;
}

char	*get_target_path(t_vec *args, char *cur_dir, char *home)
{
	char	**split_path;
	char	*ptr;
	char	*target;

	ptr = vec_get(args, 1);
	if (ft_strchr((*(char **)ptr), '/') == *(char **)ptr)
		return (*(char **)ptr);
	split_path = ft_split(cur_dir, '/');
	if (!split_path)
		return (NULL);
	target = expand_relative_paths(split_path, cur_dir, home);
	free_2d_array(split_path);
	return (target);
}


char	*expand_relative_paths(char **split_path, char	*cur_dir, char *home)
{
	int		i;
	char	*target;
	char	*temp;

	i = 0;
	target = ft_strdup(cur_dir);
	if (!target)
		return (NULL);
	while (split_path[0][i])
	{
		if (ft_strncmp(&split_path[0][i], "..", 3))
			get_parent(target);
		else if (ft_strncmp(&split_path[0][i], "~", 2))
			expand_home(target, home);
		else
		{
			temp = ft_strjoin(target, &split_path[0][i]);
			free (target);
			target = temp;
		}
		temp = target;
		target = ft_strjoin(target, "/");
		free (temp);
		i++;
	}
	return (0);
}
