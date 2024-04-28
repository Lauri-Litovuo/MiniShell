/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:00:48 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/28 17:47:45 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	skip_spaces(t_vec *input, t_shell *arg, int i, int count)
{
	while (i < arg->in_len && (input->memory[i] == ' '
		|| input->memory[i] == '\t' || input->memory[i] == '\n'))
		i++;
	return (i - count);
}

int	handle_start(t_vec *input, t_shell *arg,  int i)
{
	int	count;

	count = i;
	i += skip_spaces(input, arg, i, count);
	if (input->memory[i] == '|')
	{
		vec_free(input);
		error_msg(2, SYNTX, "`|'\n");
		return (-2000);
	}
	return (i - count);
}

int	handle_q(t_vec *input, t_shell *arg,  int i)
{
	int	count;

	count = i;
	i++;
	if (input->memory[i] == '\'')
	{
		i++;
		return (i - count);
	}
	else
	{
		while ((size_t)i < input->len && input->memory[i] != '\'')
			i++;
		if (input->memory[i] != '\'')
		{
			vec_free(input);
			error_msg(2, UNMATCH, "`''\n");
			return (-2000);
		}
		return (skip_spaces(input, arg, i, count));
	}
}

int	handle_qq(t_vec *input, t_shell *arg,  int i)
{
	int	count;

	count = i;
	i++;
	if (input->memory[i] == '\"')
	{
		i++;
		return (i - count);
	}
	else
	{
		while (i < arg->in_len && input->memory[i] != '\"')
			i++;
		if (input->memory[i] != '\"')
		{
			vec_free(input);
			error_msg(2, UNMATCH, "`\"'\n");
			return (-2000);
		}
		i++;
		return (skip_spaces(input, arg, i, count));
	}
}

int	handle_pipe(t_vec *input, t_shell *arg, int i)
{
	int	count;

	count = i;
	if (input->memory[i + 1])
		i++;
	if (input->memory[i] == '|')
	{
		vec_free(input);
		error_msg(2, SYNTX, "`|'\n");
		return (-2000);
	}
	i += skip_spaces(input, arg, i, count);
	if (!input->memory[i])
	{
		vec_free(input);
		error_msg(2, SYNTX, "`newline'\n");
		return (-2000);
	}
	if (input->memory[i] == '|')
	{
		vec_free(input);
		error_msg(2, SYNTX, "`|'\n");
		return (-2000);
	}
	return (i - count);
}
