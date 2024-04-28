/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:39:34 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/28 17:45:28 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_endofinput(t_vec *input, int i)
{
	int	ret;

	ret = i;
	if (!input->memory[i])
	{
		vec_free(input);
		error_msg(2, SYNTX, "`newline'\n");
		return (-2000);
	}
	else if (input->memory[i] == '|')
	{
		vec_free(input);
		error_msg(2, SYNTX, "`|'\n");
		return (-2000);
	}
	else
		 return (ret);
}

int	handle_great(t_vec *input, t_shell *arg,  int i)
{
	int	count;

	count = i;
	if (input->memory[i] == '>')
	{
		i++;
		if (input->memory[i] == '>')
		{
			i++;
			if (input->memory[i] == '<' || input->memory[i] == '>')
			{
				error_msg(2, SYNTX, "`<'\n");
				return (-2000);
			}
		}
		else if (input->memory[i] == '<')
		{
			vec_free(input);
			error_msg(2, SYNTX, "`<'\n");
			return (-2000);
		}
	}
	i += skip_spaces(input, arg, i, count);
	return (check_endofinput(input, i));
}

int	handle_lessgreat(t_vec *input, t_shell *arg,  int i)
{
	int	count;

	count = i;
	if (input->memory[i] == '>')
		return (handle_great(input, arg, i));
	if (input->memory[i] == '<')
	{
		i++;
		if (input->memory[i] == '<' || input->memory[i] == '>')
		{
			i++;
			if (input->memory[i] == '<' || input->memory[i] == '>')
			{
				error_msg(2, SYNTX, "`<'\n");
				return (-2000);
			}
		}
	}
	i += skip_spaces(input, arg, i, count);
	return (check_endofinput(input, i));
}
