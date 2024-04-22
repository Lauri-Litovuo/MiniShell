/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:32:59 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/22 14:04:42 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_env(t_vec *env)
{
	int	i;

	i = 0;
	while ((size_t)i < env->len)
	{
		printf("%s\n", *(char **)vec_get(env, i));
		i++;
	}
}
