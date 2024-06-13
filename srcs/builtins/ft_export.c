/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:22:49 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/13 20:17:41 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	export_variable(t_vec *env, char *arg);
static int	export_env_var(char *env_var, char *arg, t_vec *env);
void		write_export_error(char *str, char *err_msg);

int	ft_export(t_vec *env, t_vec *args)
{
	size_t		i;
	size_t		j;
	char		**arg_strs;

	i = 0;
	j = 0;
	arg_strs = (char **)args->memory;
	if (args->len == 1)
	{
		print_exports(env);
		return (0);
	}
	i++;
	while (i < args->len)
	{
		if (export_variable(env, arg_strs[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

static int	export_variable(t_vec *env, char *arg)
{
	char	*env_var;

	env_var = NULL;
	if (!arg)
		return (-1);
	if (ft_strncmp(arg, "=", 2) == 0)
		return (ft_putendl_fd("la_shell: export: `=': not a valid identifier", \
		STDERR_FILENO), -1);
	if (ft_strchr(arg, '=') == NULL)
		env_var = ft_strdup(arg);
	else
		env_var = extract_env_var(arg);
	if (env_var == NULL)
		return (-1);
	if (check_export_syntax(env_var) < 0)
		return (write_export_error(env_var, "not a valid identifier"), -1);
	else if (ft_strchr(arg, '=') != NULL
		&& export_env_var(env_var, arg, env) < 0)
	{
		ft_putendl_fd("la_shell: export: failed", STDERR_FILENO);
		return (-1);
	}
	if (env_var)
		free(env_var);
	return (0);
}

int	check_export_syntax(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (-1);
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
		return (-1);
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

static int	export_env_var(char *env_var, char *arg, t_vec *env)
{
	int			index;
	char		*temp;
	char		*remove;

	index = 0;
	remove = NULL;
	if (!arg || !env_var)
		return (-1);
	if (getenv(env_var) == 0 && find_index_of_env(env, env_var) < 0)
	{
		temp = ft_strdup(arg);
		if (!(temp) || vec_push(env, &temp) < 0)
			return (-1);
		return (0);
	}
	else
	{
		index = find_index_of_env(env, env_var);
		if (index < 0)
			return (-1);
		temp = ft_strdup(arg);
		if (!temp)
			return (-1);
		remove = *(char **)vec_get(env, index);
		if (vec_replace_str(env, temp, index) < 0)
			return (-1);
		free (remove);
	}
	return (0);
}

void	write_export_error(char *str, char *err_msg)
{
	ft_putstr_fd("la_shell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}
