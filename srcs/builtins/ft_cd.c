/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:27:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/28 16:16:01 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	update_pwd_env(t_vec *env);

int	ft_cd(t_vec *env, t_vec *args)
{
	char	**strs;
	char	*home;

	strs = (char **)args->memory;
	copy_homedir(env, home);
	if (!strs[0][1] ||
	ft_strncmp(strs[0][1], "~", ft_strlen(strs[0][1]) + 1) ||
	ft_strncmp(strs[0][1], home, ft_strlen(strs[0][1]) + 1))
		goto_home(vec, home);
	else if (ft_strncmp(strs[0][1], "/", ft_strlen(strs[0][1]) + 1))
		goto_root();
	else if (ft_strncmp(strs[0][1], "..", ft_strlen(strs[0][1]) + 1))
		goto_parent();
	else if (ft_strncmp(strs[0][1], "../..", ft_strlen(strs[0][1]) + 1))
		goto_grandparent();
	else if (access(strs[0][1], F_OK) == 0)
		goto_dir();
	else
		return (-1); //err_mngmt
}

char	*copy_homedir(t_vec *env, char *home)
{
	
}



static int	update_pwd_env(t_vec *env)
{
	char	*temp;
	int		index;
	char	cur_dir[PATH_MAX]; //check if path_max (1024) is enough or should we use 4096

	if (getcwd(cur_dir, PATH_MAX) == NULL)
		return (perror("pwd: "), -1); // err_mngmt
	index = find_index_of_env(env, "PWD");
	if (index < 0)
		return (printf("error in update_pwd_env1"), -1);// err_mngmt
	temp = ft_strdup(cur_dir);
	if (temp == NULL)
		return (printf("error in update_pwd_env2"), -1);// err_mngmt
	vec_replace_str(env, temp, index);
		return (printf("error in update_pwd_env4"), -1);// err_mngmt
	return (0);
}
