/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:32:59 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/15 21:21:54 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_env(t_vec *env, t_exec *exe)
{
	int	i;

	i = 0;
	if (exe->cmd_argv[1] != NULL)
		return (-1);
	while ((size_t)i < env->len)
	{
		if (vec_get(env, i) == NULL)
			return (-1);
		printf("%s\n", *(char **)vec_get(env, i));
		i++;
	}
	return (0);
}

int	ft_pwd(t_shell *arg)
{
	printf("%s\n",arg->pwd);
	return (0);
}

void	write_unset_error(char *str, char *err_msg)
{
	ft_putstr_fd("la_shell: unset: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

int	ft_unset(t_vec *env, t_vec *args)
{
	int				index;
	size_t			i;
	char			*env_var;

	index = 0;
	i = 1;
	while (i < args->len)
	{
		env_var = *(char **)vec_get(args, i);
		if (check_export_syntax(env_var) < 0)
			write_unset_error(env_var, "not a valid identifier");
		if (find_index_of_env(env, env_var) >= 0)
		{
			env_var = *(char **)vec_get(args, i);
			index = find_index_of_env(env, env_var);
			if (vec_remove_str(env, index) < 0)
				return (1);
		}
		i++;
	}
	return (0);
}
