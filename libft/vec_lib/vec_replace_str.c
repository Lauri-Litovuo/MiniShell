/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_replace_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:30:47 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/13 12:07:49 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	vec_replace_str(t_vec *dst, void *src, size_t index)
{
	char	*str;

	if (!dst || !src || index > dst->len)
		return (-1);
	str = *(char **)vec_get(dst, index);
	if (vec_remove(dst, (size_t)index) < 0)
		return (-1);
	if (vec_insert(dst, &src, index) < 0)
		return (-1);
	free(str);
	return (1);
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
		printf("env%d: %s\n", i, *(char **)vec_get(env, i));
		i++;
	}
	return (0);
}

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

int main(int ac, char **av, char **envp)
{
	t_vec env;
	char test[] = "SHLVL=3";
	int	index;

	printf("%s\n", av[0]);
	copy_env (&env, envp);
	index = find_index_of_env(&env, "SHLVL=1");
	printf("index: %d\n", index);
	vec_replace_str(&env, test, index);
	for(size_t i = 0; i < env.len; i++)
		printf("env%zu: %s\n", i, *(char **)vec_get(&env, i));
	vec_free_str(&env);
	return (ac);
}*/
