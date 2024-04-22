/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/22 12:53:59 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	copy_env(t_vec *env, char **envp);

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_vec	env;

	(void)argc;
	(void)argv;
	copy_env(&env, envp);
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			buf = readline("Shell> ");
			if (!buf)
			{
				perror ("Exiting shell");
				exit (1);
			}
			printf("User input is: %s\n", buf);
			if (buf && *buf)
				add_history(buf);
			free(buf);
		}
		else
			printf ("is not interactive with terminal\n");
	}
	free(buf);
	return (0);
}

static int	copy_env(t_vec *env, char **envp)
{
	char	*temp;
	int		i;

	i = 0;
	if (vec_new(env, 50, sizeof(char *)) < 0)
		return (-1);
	printf("alloc_size: %zu\n", env->alloc_size);
	printf("element size: %zu\n", env->elem_size);
	printf("sizeof: %lu\n", sizeof(char *));
	if (!envp)
		return (-1);
	while (envp[i])
	{
		temp = ft_strdup(envp[i]);
		printf("temp:%s\n", temp);
		if (vec_push(env, &temp) < 0)
		{
			vec_free(env);
			return (-1);
		}
		printf("env: %s\n", *(char **)vec_get(env, i));
		free(temp);
		i++;
	}
	return (0);
}
