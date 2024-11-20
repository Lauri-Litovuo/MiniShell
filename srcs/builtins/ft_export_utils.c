/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:35:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/11/20 14:14:45 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	print_strings(t_vec *temp);

void	print_exports(t_vec *env)
{
	t_vec	temp;
	int		index;

	if (env->len == 0)
		return ;
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

	i = 0;
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
