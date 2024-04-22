/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:32:59 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/22 15:29:43 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(t_vec *env)
{
	int	i;

	i = 0;
	while ((size_t)i < env->len)
	{
		if (vec_get(env, i) == NULL)
		{
			//builtin_error(ENV);
			return (1);
		}
		printf("%s\n", *(char **)vec_get(env, i));
		i++;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	cur_dir[PATH_MAX]; //check if path_max (1024) is enough or should we use 4096

	if (getcwd(cur_dir, PATH_MAX) == NULL)
	{
		perror("pwd: ");
		return (1);
	}
	else
		printf("%s\n", cur_dir);
	return (0);
}
