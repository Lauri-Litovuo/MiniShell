/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:16:15 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/15 23:38:42 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	copy_homedir(t_vec *env, t_cd *data, t_shell *arg)
{
	int		index;

	index = find_index_of_env(env, "HOME");
	if (index < 0)
	{
		ft_bzero(data->home, PATH_MAX);
		ft_strlcpy(data->home, arg->home, PATH_MAX);
		return (0);
	}
	ft_strlcpy(data->home, (*(char **)vec_get(env, index) + 5), PATH_MAX);
	return (0);
}

int	goto_home(t_vec *env, t_cd *data, t_shell *arg, int squiqly)
{
	if (squiqly == 1)
	{
		ft_bzero(data->home, PATH_MAX);
		ft_strlcpy(data->home, arg->home, PATH_MAX);
	}
	else if (squiqly == 0 && find_index_of_env(env, "HOME=") < 0)
	{
		ft_putstr_fd("la_shell: cd: HOME not set\n", STDERR_FILENO);
		return (-1);
	}
	else
		ft_strlcat(data->path, data->home, PATH_MAX);
	if (access(data->home, F_OK) == 0)
	{
		if (chdir(data->home) != 0)
			return (perror ("cd to ~ failed"), -1);
		ft_strlcpy(data->target, data->home, PATH_MAX);
		if (update_pwd_cd(env, data, arg) < 0)
			return (-1);
	}
	else
		return (home_error(data, 2), -1);
	return (0);
}

int	goto_root(t_vec *env, t_cd *data, t_shell *arg)
{
	ft_strlcpy(data->target, "/", PATH_MAX);
	if (access("/", F_OK) == 0)
	{
		if (chdir("/") != 0)
		{
			perror ("cd to / failed");
			return (-1);
		}
		if (update_pwd_cd(env, data, arg) < 0)
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

int	expand_home(t_cd *data, t_vec *env)
{
	if (find_index_of_env(env, "HOME=") < 0)
	{
		ft_putstr_fd("la_shell: cd: HOME not set\n", STDERR_FILENO);
		return (-1);
	}
	ft_bzero(data->target, PATH_MAX);
	ft_strlcpy(data->target, data->home, PATH_MAX);
	ft_strlcat(data->target, "/", PATH_MAX);
	return (0);
}
