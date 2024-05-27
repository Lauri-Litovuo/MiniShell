/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:32:59 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/27 13:19:57 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(t_vec *env, t_exec *exe)
{
	int	i;

	i = 0;
	printf("trying to print %zu vars\n", env->len);
	if (exe->cmd_argv[1] != NULL)
	{
		ft_fprintf("Minishell : env: too many arguments");
		return (-1);
	}
	while ((size_t)i < env->len)
	{
		if (vec_get(env, i) == NULL)
		{
			ft_printf("Minishell: vec_get: failed");
			return (1);
		}
		printf("%s\n", *(char **)vec_get(env, i));
		i++;
	}
	return (0);
}

int	ft_pwd(t_vec *env)
{
	int		index;
	char	*cur_dir;
	char	cwd[PATH_MAX];

	index = 0;
	cur_dir = NULL;
	index = find_index_of_env(env, "PWD");
	if (index >= 0)
		cur_dir = *(char **)vec_get(env, index);
	else
	{
		if (getcwd(cwd, PATH_MAX) == NULL)
		{
			perror("pwd: ");
			return (-1);
		}
	}
	if (cur_dir)
		printf("%s\n", cur_dir + 4);
	else
		printf("%s\n", cwd);
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
		if (find_index_of_env(args, env_var) >= 0)
		{
			index = find_index_of_env(env, env_var);
			if (index == -1)
				return (ft_putstr_fd("Minishell: unset", 2), -1);
			free (env_var);
			env_var = vec_get(env, index);
			if (vec_remove_str(env, index) < 0)
				return (ft_putstr_fd("Minishell: unset", 2), -1);
		}
		i++;
	}
	return (0);
}
