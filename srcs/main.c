/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/13 12:12:00 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	init_index(t_shell *arg)
{
	arg->count = 0;
	arg->pipe_count = 0;
	arg->gl_count = 0;
	arg->i = 0;
	arg->j = 0;
}

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
		// printf("env: %s\n", *(char **)vec_get(env, i));
		// printf("temp:%s\n", temp);
		if (vec_push(env, &temp) < 0)
			return (error_msg_free(1, VECPUSH, NULL, env));
		// printf("env: %s\n", *(char **)vec_get(env, i));
		// free(temp);
		i++;
	}
	return (0);
}

int	miniloop(t_vec *env, char *buf, t_shell *arg)
{
	while (1)
	{
		init_index(arg);
		if (isatty(STDIN_FILENO) == 1)
		{
			buf = readline("minishell> ");
			if (!buf)
			{
				exit (1);
			}
			launch_builtin(env, buf);
			parse_input(arg, buf);
			if (buf && *buf)
				add_history(buf);
			free(buf);
		}
		else
			printf ("is not interactive with terminal\n");
	}
	return (0);
}

int minishell(char **envp)
{
	char	*buf;
	t_vec	env;
	t_shell	arg;

	buf = NULL;
	ft_memset(&arg, 0 , sizeof(t_shell));
	copy_env(&env, envp);
	miniloop(&env, buf, &arg);
	free(buf);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1 && argv && envp && *envp)
		return (minishell(envp));
	else
		return (1);
}
