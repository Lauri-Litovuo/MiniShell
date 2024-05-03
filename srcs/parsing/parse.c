/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:10:11 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/03 15:55:01 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	set_count(t_shell *arg)
{
	if (arg->pipe_count == 0 && arg->gl_count == 0)
		arg->count = 1;
	else if (arg->gl_count > 0 && arg->pipe_count > 0)
		arg->count = arg->pipe_count + 1;
	else if (arg->gl_count > 0 && arg->pipe_count == 0)
		arg->count = 1;
	else
		arg->count = arg->pipe_count + 1;
}

void	init_count(char *buf, t_shell *arg, int i)
{
	while (buf[i])
	{
		if (buf[i] == '\'')
			i = handle_q(buf, i);
		else if (buf[i] == '\"')
			i = handle_qq(buf, i);
		else if (buf[i] == '|')
		{
			arg->pipe_count = arg->pipe_count + 1;
			i = handle_pipe(buf, i);
		}
		else if (buf[i] == '>' || buf[i] == '<')
		{
			arg->gl_count = arg->gl_count + 1;
			i = handle_lessgreat(buf, i);
		}
		else
			i++;
	}
	set_count(arg);
}

int	scan_input(char *buf)
{
	int	i;

	i = 0;
	i = handle_start(buf, i);
	if (i < 0)
		return (-1);
	while (buf[i])
	{
		if (i < 0)
			return (-1);
		if (buf[i] == '\'')
			i = handle_q(buf, i);
		else if (buf[i] == '\"')
			i = handle_qq(buf, i);
		else if (buf[i] == '|')
			i = handle_pipe(buf, i);
		else if (buf[i] == '>' || buf[i] == '<')	
			i = handle_lessgreat(buf, i);
		else
			i++;
	}
	if (i < 0)
		return (-1);
	return (0);
}

int	split(char *buf, t_shell *arg)
{
	// char	*temp;
	int		ret;

	ret = 0;
	while (arg->i < arg->count)
	{
		if (arg->i == 0)
		{
			if (split_input(buf, arg, 0, 0) < 0)
				return (-1);
		}
		else
		{
			if (split_rest(buf, arg, arg->i) < 0)
				return (-1);
		}
		arg->i++;
	}
	return (0);
	
	// temp = ft_substr(buf, 0, 3);
	// vec_new(&arg[arg->i].cmd, 1, sizeof(char *));
	// vec_push(&arg[arg->i].cmd, &temp);
	
	// arg->i++;
	// temp = ft_substr(buf, 3, 4);
	// vec_new(&arg[arg->i].cmd, 1, sizeof(char *));
	// vec_push(&arg[arg->i].cmd, &temp);
}

int	parse_input(t_shell *arg, char *buf)
{
	int		i;
	
	i = 0;
	if (scan_input(buf) == -1)		//checks for syntax errors
		return (-1);
	init_count(buf, arg, i);			//  stores count of args && count of pipes/redirections
	if (split(buf, arg) == -1)
		return (-1);
	// printf("arg[0].cmd: %s\n", &arg[0].cmd.memory[0]);
	// printf("arg[0].cmd: %s\n", &arg[0].cmd.memory[1]);
	printf("arg[0].cmd: %s\n", *(char **)vec_get(&arg[0].cmd, 0));
	printf("arg[0].cmd: %s\n", *(char **)vec_get(&arg[0].cmd, 0));
	printf("arg[1].cmd: %s\n", *(char **)vec_get(&arg[1].cmd, 0));
	printf("arg[2].cmd: %s\n", *(char **)vec_get(&arg[2].cmd, 0));
	return (1);
}
