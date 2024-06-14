/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:40:30 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/14 14:41:39 by llitovuo         ###   ########.fr       */
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
	if (ft_strchr(arg, '+') + 1 == ft_strchr(arg, '='))
	{
		env = ft_strchr(arg, '+');
		len = ft_strlen(arg) - ft_strlen(env);
		env = ft_substr(arg, 0, len);
		if (env == NULL)
			return (NULL);
	}
	else
	{
		env = ft_strchr(arg, '=');
		len = ft_strlen(arg) - ft_strlen(env);
		env = ft_substr(arg, 0, len);
		if (env == NULL)
			return (NULL);
	}
	return (env);
}

int	update_pwd_env(t_vec *env, char *dir)
{
	char	*temp;
	int		index;
	char	*remove;

	index = find_index_of_env(env, "PWD");
	if (index < 0)
		return (-1);
	temp = ft_strdup(dir);
	if (temp == NULL)
		return (-1);
	remove = *(char **)vec_get(env, index);
	if (!remove)
		return (-1);
	if (vec_replace_str(env, temp, index) < 0)
	{
		free (remove);
		return (-1);
	}
	free (remove);
	return (0);
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}
