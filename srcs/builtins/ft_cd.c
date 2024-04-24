/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:27:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/24 12:12:46 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	update_pwd_env(t_vec *env);

int	ft_cd(t_vec *env, t_vec *args)
{
	if (cd only or cd ~ go to home eg. /Users/llitovuo);
	else if(cd / goes to PWD=/)
	else if(.. go one level up, if not on root);
	else if (../.. go two levels up etc. if possible)
	else if (cd [dirname] goes to that path)
	
}

static int	update_pwd_env(t_vec *env)
{
	char	cur_dir[PATH_MAX]; //check if path_max (1024) is enough or should we use 4096
	char	*temp;
	int		index;

	if (getcwd(cur_dir, PATH_MAX) == NULL)
		return (perror("pwd: "), -1); // err_mngmt
	index = find_index_of_env(env, "PWD");
	if (index < 0)
		return (printf("error in update_pwd_env1"), -1);// err_mngmt
	if (vec_remove(env, index) < 0)
		return (printf("error in update_pwd_env2"), -1);// err_mngmt
	temp = ft_strdup(cur_dir);
	if (vec_push(env, temp) < 0)
		return (printf("error in update_pwd_env2"), -1);// err_mngmt
	return (0);
}
