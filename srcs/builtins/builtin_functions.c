/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:32:59 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/23 16:00:30 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(t_vec *env, t_vec *args)
{
	int	i;

	i = 0;
	if (args->len > 1)
	{
		printf("env: No options or arguments possible"); //change to error mngmt
		return (-1);
	}
	while ((size_t)i < env->len)
	{
		if (vec_get(env, i) == NULL)
		{
			printf("vec_get failed"); //change this to error mngmt
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


int	ft_unset(t_vec *env, t_vec *args)
{
	int				index;
	int				i;
	char			**env_arg;

	index = 0;
	i = 1;
	while (args->memory[i])
	{
		env_arg = (char **)args->memory;
		if (getenv((char *)env_arg) != 0)
		{
			index = find_index_of_env(env, (char *)env_arg);
			if (index == -1)
				return (-1);
			if (vec_remove(env, index) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}
