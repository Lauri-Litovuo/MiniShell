/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:40:30 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/24 09:56:07 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	find_index_of_env(t_vec *src, char *str)
{
	void	*ptr;
	int		i;

	i = 0;
	if (!src || !src->memory || !str)
		return (-1);
	while ((size_t)i < src->len)
	{
		ptr = vec_get(src, i);
		if (!ptr)
			return (-1);
		if (ft_strncmp(*(char **)ptr, str, ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_env_var(char *arg)
{
	char	*env;
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	env = ft_strchr(arg, '=');
	len = ft_strlen(arg) - ft_strlen(env);
	env = ft_substr(arg, 0, len);
	if (env == NULL)
		return (NULL);
	return (env);
}
