/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/29 16:04:24 by aneitenb         ###   ########.fr       */
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
	arg->join_flag = -1;
	arg->end_flag = 0;
	arg->expand_flag = 0;
	arg->joinrd_flag = -1;
	arg->endrd_flag = 0;
	arg->expandrd_flag = 0;
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
			return (error_msg_free(1, VECPUSH, NULL, env));
		i++;
	}
	return (0);
}

int	miniloop(char *buf, t_shell *arg)
{
	while (1)
	{
		init_index(arg);
		buf = readline("la_shell> ");
		if (!buf)
		{
			printf("exit\n");//
			free_arg(arg, YES);
			exit (1);
		}
		if (*buf != '\0')
		{
			parse_input(arg, buf);
			execute(arg);
			if (buf && *buf)
				add_history(buf);	
		}
		free(buf);
		free_arg(arg, NO);
	}
	free_arg(arg, YES);
	return (0);
}

int	minishell(char **envp)
{
	char	*buf;
	t_shell	arg;

	buf = NULL;
	ft_memset(&arg, 0, sizeof(t_shell));
	copy_env(&arg.env, envp);
	miniloop(buf, &arg);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	signal(SIGQUIT, SIG_IGN);
	set_signals();
	if (argc == 1 && argv && envp && *envp)
		return (minishell(envp));
	else
		return (1);
}
