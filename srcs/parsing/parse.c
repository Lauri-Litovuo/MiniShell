/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:10:11 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/20 17:41:10 by aneitenb         ###   ########.fr       */
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

/****************************************
*	Stores count of arguments and 		*
*	count of pipes/redirections.		*
*	Returns: -1 on error, 0 on success.	*
*****************************************/
void	init_count(char *buf, t_shell *arg)
{
	int	i;

	i = 0;
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

/****************************************
*	Checks for syntax errors.			*
*	Returns: -1 on error, 0 on success.	*
*****************************************/
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

/*		DELETE		*/
void	print_vectors(t_shell *arg)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < arg->count)
	{
		j = 0;
		while (j < arg[i].cmd.len)
		{
			printf("arg[%zu], cmd[%zu]: %s\n", i, j,
				*(char **)vec_get(&arg[i].cmd, j));
			j++;
		}
		j = 0;
		while (j < arg[i].rdrct.len)
		{
			printf("arg[%zu], rdrct[%zu]: %s\n", i, j,
				*(char **)vec_get(&arg[i].rdrct, j));
			j++;
		}
		i++;
	}
}

int	split(char *buf, t_shell *arg)
{
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
		// printf("joinRD flag: %d\n", arg->joinrd_flag);
		// printf("endRD flag: %d\n", arg->endrd_flag);
		if (arg->end_flag > 0 || arg->endrd_flag > 0)
			if (vec_join(arg, arg->i) < 0)
				return (-1);
		arg->i++;
	}
	return (0);
}


int	parse_input(t_shell *arg, char *buf)
{
	if (scan_input(buf) == -1)
		return (-1);
	init_count(buf, arg);
	if (split(buf, arg) == -1)
		return (-1);
	print_vectors(arg);
	return (1);
}
