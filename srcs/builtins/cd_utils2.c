/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:14:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/15 23:20:06 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	goto_dir(t_cd *data, t_vec *env, t_shell *arg)
{
	if (chdir(data->target) != 0)
	{
		perror ("no access:");
		return (-1);
	}
	if (update_pwd_cd(env, data, arg) < 0)
		return (-1);
	return (0);
}

int	expand_cur_dir(t_cd *data, char *str)
{
	if (ft_strncmp(str, ".", 2) != 0)
	{
		ft_putstr_fd("ls_shell: cd: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (-1);
	}
	ft_bzero(data->target, PATH_MAX);
	ft_strlcpy(data->target, data->cur_dir, PATH_MAX);
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
	ft_bzero(data->old_pwd, PATH_MAX);
	ft_strlcpy(data->old_pwd, "OLDPWD=", PATH_MAX);
	data->ptr = NULL;
	data->split_path = NULL;
}

int	update_pwd_cd(t_vec *env, t_cd *data, t_shell *arg)
{
	int		index;
	char	*temp;
	char	*remove;

	ft_bzero(arg->pwd, PATH_MAX);
	ft_strlcpy(arg->pwd, data->target, PATH_MAX);
	index = find_index_of_env(env, "PWD=");
	if (index < 0)
		return (0);
	if (data->path[ft_strlen(data->path) - 1] == '/'
		&& data->target[0] == '/' && data->target[1])
		ft_strlcat(data->path, data->target + 1, PATH_MAX);
	else
		ft_strlcat(data->path, data->target, PATH_MAX);
	temp = ft_strdup(data->path);
	if (!temp)
		return (-1);
	remove = *(char **)vec_get(env, index);
	if (vec_replace_str(env, temp, index) < -1)
		return (-1);
	free (remove);
	return (0);
}

int	update_old_pwd(t_vec *env, t_cd *data)
{
	char	*temp;
	int		index;
	char	*remove;

	index = 0;
	remove = NULL;
	ft_strlcat(data->old_pwd, data->cur_dir, PATH_MAX);
	temp = ft_strdup(data->old_pwd);
	index = find_index_of_env(env, "OLDPWD=");
	if (index < 0)
	{
		if (vec_push(env, &temp) < 0)
			return (-1);
	}
	else
	{
		remove = *(char **)vec_get(env, index);
		if (vec_replace_str(env, temp, index) < 0)
			return (-1);
		free (remove);
	}
	return (0);
}
