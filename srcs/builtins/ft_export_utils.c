/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:35:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/26 14:42:36 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	print_strings(t_vec *temp);

void	print_exports(t_vec *env)
{
	t_vec	temp;
	int		index;

	vec_new(&temp, env->len, env->elem_size);
	if (vec_copy_len(&temp, env) < 0)
		return ;
	index = find_index_of_env(&temp, "_=");
	if (index > 0)
		vec_remove(&temp, index);
	else
		return ;
	vec_sort_alpha(&temp);
	print_strings(&temp);
	vec_free(&temp);
}

static void	print_strings(t_vec *temp)
{
	size_t	i;
	char	*var_name;
	char	**vec_ptr;

	i = 0;
	vec_ptr = (char **)temp;
	while (i < temp->len)
	{
		printf("declare -x ");
		var_name = extract_env_var(*(char **)vec_get(temp, i));
		printf("%s", var_name);
		printf("=");
		printf("\"");
		printf("%s", *(char **)vec_get(temp, i) + ft_strlen(var_name) + 1);
		printf("\"\n");
		free(var_name);
		i++;
	}
}

/*
static int	copy_env(t_vec *env, char **envp)
{
	char	*temp;
	int		i;

	i = 0;
	if (vec_new(env, 50, sizeof(char *)) < 0)
		return (-1);
	if (!envp)
		return (-1);
	while (envp[i])
	{
		temp = ft_strdup(envp[i]);
		if (vec_push(env, &temp) < 0)
		{
			vec_free(env);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_vec	env;

	printf("%s\n", av[0]);
	copy_env (&env, envp);
	print_exports(&env);
	vec_free_str(&env);
	vec_free(&env);
	return (ac);
}
*/
