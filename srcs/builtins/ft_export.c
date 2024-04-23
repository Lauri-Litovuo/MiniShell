/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:22:49 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/23 16:04:57 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// Should be tested if export works otherwise than as a first argument in bash.
// Should test whether "export" should work solely without arguments, if so original t_vec env should be saved somewhere

static int	check_export_syntax(char *arg);
static int	export_variable(t_vec *env, char *arg);
static char	*extract_env_var(char *arg);
static int	export_env_var(char *env_var, char *arg, t_vec *env);

int	ft_export(t_vec *env, t_vec *args)
{
	int		i;
	int		j;
	char	**arg_strs;

	i = 0;
	j = 0;
	arg_strs = (char **)args->memory;
	if (args->len == 1)
	{
		while ((size_t)j < env->len)
		{
			if (vec_get(env, j) == NULL)
			{
				printf("error in export1"); //change to error mngmt
				return (1);
			}
			printf("%s\n", *(char **)vec_get(env, j));
			i++;
		}
	}
	while (args->memory[++i])
	{
		if (export_variable(env, arg_strs[i]))
			printf("error in export2"); //change to error mngmt
	}
	return (0);
}

static int	export_variable(t_vec *env, char *arg)
{
	char	*env_var;

	env_var = NULL;
	if (ft_strchr(arg, '=') != NULL)
	{
		env_var = extract_env_var(arg);
		if (env_var == NULL)
			return (-1);
		if (check_export_syntax(env_var) < 0)
		{
			return (printf("bash: export: `L+OL=hello.world': not a valid identifier"), -1); //exitcode 1;
		}
		else
		{
			if (export_env_var(env_var, arg, env) < 0)
				return (-1);
		}
		free(env_var);
	}
	return (0);
}


static int	check_export_syntax(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 || arg[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

static char	*extract_env_var(char *arg)
{
	char	*env;
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	env = ft_strchr(arg, '=');
	len = ft_strlen(arg) - ft_strlen(env);
	//free (env);
	env = ft_substr(arg, 0, len);
	if (env == NULL)
		return (NULL);
	return (env);
}

static int	export_env_var(char *env_var, char *arg, t_vec *env)
{
	int	index;

	index = 0;
	if (getenv(env_var) == NULL)
	{
		if (vec_push(env, arg) < 0)
			return (-1);
		return (0);
	}
	else
	{
		index = find_index_of_env(env, env_var);
		if (index < 0)
			return (-1);
		else if (vec_remove(env, index) < 0 || vec_insert(env, arg, index) < 0)
			return (-1);
	}
	return (0);
}
