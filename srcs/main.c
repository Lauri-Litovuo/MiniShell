/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/14 15:09:33 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	g_signal;

void	init_index(t_shell *arg)
{
	arg->temp = NULL;
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
	arg->split_flag = 0;
	arg->pids = NULL;
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
		if (!temp)
			return (-1);
		if (vec_push(env, &temp) < 0)
		{
			return (error_msg(1, VECPUSH, NULL));
		}
		i++;
	}
	return (0);
}

int	miniloop(char *buf, t_shell *arg)
{
	while (1)
	{
		init_index(arg);
		signals_default();
		buf = readline("✨🐢✨la_shell> ");
		enabled_termios();
		check_signal(arg);
		if (!buf)
			handle_buf(arg);
		if (buf && *buf)
			add_history(buf);
		if (*buf == '\0')
			arg->exit_code = 0;
		if (*buf != '\0')
		{
			if (parse_input(arg, buf) == -1)
				continue ;
			execute(arg);
			system("leaks -q minishell");
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

	g_signal = 0;
	buf = NULL;
	ft_memset(&arg, 0, sizeof(t_shell));
	if (copy_env(&arg.env, envp) < 0)
		free_arg(&arg, YES);
	miniloop(buf, &arg);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1 && argv && envp && *envp)
		return (minishell(envp));
	else
		return (1);
}
