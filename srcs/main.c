/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/29 09:41:24 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

static int	copy_env(t_vec *env, char **envp);

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*buf;
// 	t_vec	env;
// 	t_vec	larg;
// 	t_shell	sh;

// 	argc = 0;
// 	argv = NULL;
// 	init_index(&sh);
// 	copy_env(&env, envp);
// 	// printf("env: %s\n", *(char **)vec_get(&env, 9));
// 	while (1)
// 	{
// 		if (isatty(STDIN_FILENO) == 1)
// 		{
// 			buf = readline("minishell> ");
// 			if (!buf)
// 			{ 
// 				perror ("Exiting shell");
// 				exit (1);
// 			}
// 			if (parse_input(&larg, &sh, buf) == -1)
// 				return (-1);
// 			while (sh.k < larg.len)	//printing vector larg
// 			{
// 				printf("larg[%zu]: %s\n", sh.k, *(char **)vec_get(&larg, sh.k));
// 				sh.k++;
// 			}
// 			if (buf && *buf)
// 				add_history(buf);
// 			free(buf);
// 		}
// 		else
// 			printf ("is not interactive with terminal\n");
// 	}
// 	free(buf);
// 	return (0);
// }
void	init_index(t_shell *arg)
{
	arg->count = 0;
	arg->pipe_count = 0;
	arg->gl_count = 0;
	arg->i = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	t_vec	env;
	t_shell	arg;
	// size_t	i = 0;

	argc = 0;
	argv = NULL;
	ft_memset(&arg, 0 , sizeof(t_shell));
	init_index(&arg);
	copy_env(&env, envp);
	while (1)
	{
		init_index(&arg);
		if (isatty(STDIN_FILENO) == 1)
		{
			buf = readline("minishell> ");
			if (!buf)
			{ 
				perror ("Exiting shell");
				exit (1);
			}
			if (parse_input(&arg, buf) == -1)
				return (-1);
			printf("arg count:%zu\n", arg.count);
			printf("redirections count:%zu\n", arg.gl_count);
			printf("pipe count:%zu\n", arg.pipe_count);
			// while (i < arg.len)	//printing vectors of struct arg
			// {
			// 	printf("arg[%zu], cmd: %s\n", i, *(char **)vec_get(&arg.cmd, i));
			// 	printf("arg[%zu], rdrct: %s\n", i, *(char **)vec_get(&arg.rdrct, i));
			// 	i++;
			// }
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
	// printf("alloc_size: %zu\n", env->alloc_size);
	// printf("element size: %zu\n", env->elem_size);
	// printf("sizeof: %lu\n", sizeof(char *));
	if (!envp)
		return (-1);
	while (envp[i])
	{
		temp = ft_strdup(envp[i]);
		// printf("temp:%s\n", temp);
		if (vec_push(env, &temp) < 0)
			return (error_msg_free(1, VECPUSH, NULL, env));
		// printf("env: %s\n", *(char **)vec_get(env, i));
		// free(temp);
		i++;
	}
	return (0);
}
