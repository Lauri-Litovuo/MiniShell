/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:32:59 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/06 12:21:29 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(t_vec *env, t_vec *args)
{
	int	i;

	i = 0;
	if (args->len > 1)
	{
		printf("env: No options or arguments possible\n"); //errmngm
		return (-1);
	}
	while ((size_t)i < env->len)
	{
		if (vec_get(env, i) == NULL)
		{
			printf("vec_get failed\n"); //errmng
			return (1);
		}
		printf("%s\n", *(char **)vec_get(env, i));
		i++;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	cur_dir[PATH_MAX]; //check if path_max (1024) or should be 4096
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
	char			**env_args;
	char			*env_var;

	index = 0;
	i = 1;
	env_args = (char **)args->memory;
	while ((size_t)i < args->len)
	{
		env_var = extract_env_var(env_args[i]);
		if (getenv(env_var) != 0 || find_index_of_env(args, env_var) >= 0)
		{
			index = find_index_of_env(env, env_var);
			if (index == -1)
				return (-1); // err_mngmt
			free (env_var);
			env_var = vec_get(env, index);
			if (vec_remove_str(env, index) < 0)
				return (-1); //err_mngmnt
		}
		i++;
	}
	return (0);
}
