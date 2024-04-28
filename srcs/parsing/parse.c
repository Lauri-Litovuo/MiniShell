/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:10:11 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/28 18:25:55 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	init_count(t_vec *input, t_shell *arg, int i)
{
	printf("arg->in_len:%d\n", arg->in_len);
	while (i < arg->in_len)
	{
		if (input->memory[i] == '\'')
			i += handle_q(input, arg, i);
		else if (input->memory[i] == '\"')
			i += handle_qq(input, arg, i);
		else if (input->memory[i] == '|')
		{
			arg->pipe_count = arg->pipe_count + 1;
			i += handle_pipe(input, arg, i);
		}
		else if (input->memory[i] == '>' || input->memory[i] == '<')
		{
			arg->gl_count = arg->gl_count + 1;
			i += handle_lessgreat(input, arg, i);
		}
		else
			i++;
	}
	if (arg->pipe_count == 0 && arg->gl_count == 0)
		arg->count = 1;
	else if (arg->gl_count > 0)
		arg->count = arg->gl_count;
	else
		arg->count = arg->pipe_count + 1;
	printf("arg count:%zu\n", arg->count);
	printf("redirections count:%zu\n", arg->gl_count);
	printf("pipe count:%zu\n", arg->pipe_count);
}

int	scan_input(t_vec *input, t_shell *arg)
{
	int	i;

	i = 0;
	i += handle_start(input, arg, i);
	if (i < 0)
		return (-1);
	while ((size_t)i < input->len)
	{
		if (i < 0)
			return (-1);
		if (input->memory[i] == '\'')
			i += handle_q(input, arg, i);
		else if (input->memory[i] == '\"')
			i += handle_qq(input, arg, i);
		else if (input->memory[i] == '|')
			i += handle_pipe(input, arg, i);
		else if (input->memory[i] == '>' || input->memory[i] == '<')	
			i += handle_lessgreat(input, arg, i);
		else
			i++;
	}
	if (i < 0)
		return (-1);
	return (0);
}

// t_shell	split_input(t_vec *input, t_shell *arg)
// {
	
// }

int	parse_input(t_shell *arg, char *buf)
{
	t_vec	input;
	int		i;
	
	i = 0;
	arg->in_len = ft_strlen(buf);
	if (vec_new(&input, 1, sizeof(char *)) < 0)
		return (error_msg(1, VECNEW, NULL));
	if (vec_push(&input, &buf) < 0)
		return (error_msg_free(1, VECPUSH, NULL, &input));
	if (!input.memory)
		return (1);
	if (scan_input(&input, arg) == -1)		//checks for syntax errors
		return (-1);
	while (i < arg->in_len)
	{
		printf("WHAT?\n");
		printf("input memory: %c", input.memory[i]);
		i++;
	}
	printf("\n");
	i = 0;
	init_count(&input, arg, i);			//  stores count of args && count of pipes
	// printf("arg count:%zu\n", arg->count);
	// printf("pipe count:%zu\n", arg->pipe_count);
	// printf("redirections count:%zu\n", arg->gl_count);
	// while (arg->i < arg->count)
	// {
	// 	arg[arg->i] = split_input(&input, arg);
	// 	arg->i++;
	// }
	
	// size_t	i = 0;
	// while (i < input.len)	//printing vector larg
	// {
	// 	printf("larg[%zu]: %s\n", i, *(char **)vec_get(&input, i));
	// 	i++;
	// }
	return (1);
}
