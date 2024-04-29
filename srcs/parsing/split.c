/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:53:19 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/29 16:47:23 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
int	store_norm(char *buf, t_shell *arg, size_t pos, int i)
{
	//create temp substr 
	// store temp to vector : arg[pos].cmd
	//skip space and end if <  or |
	//otherwise store next str
	//return -2000 on error
	return (i);
}

int	store_great(char *buf, t_shell *arg, size_t pos, int i)
{
	// store > or >> to vector : arg[pos].rdrct
	//skip whitespace
	//store following str to vector : arg[pos].rdrct
	//i++; or i += 2;
	// set flag to 1
	//return -2000 on error
	return (i);
}

int	store_less(char *buf, t_shell *arg, size_t pos, int i)
{
	// store < or << to vector : arg[pos].rdrct
	//i++; or i += 2;
	// set flag to 1
	//return -2000 on error
	return (i);
}

int	store_qq(char *buf, t_shell *arg, size_t pos, int i)
{
	// check_qq("check if operator in between, then we'll either include q or not");
	// skip empty quotes;
	// save any str between quotes into vector: arg[pos].cmd/rdrct depending on flag
	//return -2000 on error
	return (i);
}

int	store_q(char *buf, t_shell *arg, size_t pos, int i)
{
	// check_q("check if operator in between, then we'll either include q or not");
	// skip empty quotes;
	// save any str between quotes into vector: arg[pos].cmd/rdrct depending on flag
	//return -2000 on error
	return (i);
}

int	init_vectors(char *buf, t_shell *arg, size_t pos, int i, int j)
{
	while (buf[i])
	{
		i = skip_spaces(buf, i);
		if (buf[i] == '|')
			return (0);
		else if (buf[i] == '\'')
			i = store_q(buf, arg, arg->i, i);
		else if (buf[i] == '\"')
			i = store_qq(buf, arg, arg->i, i);
		else if (buf[i] == '<')
			i = store_less(buf, arg, arg->i, i);
		else if (buf[i] == '>')
			i = store_great(buf, arg, arg->i, i);
		else 
			i = store_norm(buf, arg, arg->i, i);
		if (i < 0)
			return (-1);
	}
	if (i < 0)
		return (-1);
	return (0);
}

int	split_input(char *buf, t_shell *arg, size_t pos, int i)
{
	int		j;
	
	j = 0;
	arg->i = pos;
	if (vec_new(&arg[arg->i].cmd, 1, sizeof(char *)) < 0)
		return (-1);
	if (vec_new(&arg[arg->i].rdrct, 1, sizeof(char *)) < 0)
		return (-1);
	if (init_vectors(buf, arg, arg->i, i , j) == -1)
		return (-1);
	return (0);
}

int	split_rest(char *buf, t_shell *arg, size_t pos)
{
	size_t count;
	int		i;
	
	i = 0;
	count = 0;
	while (buf[i] && count < pos)
	{
		if (buf[i] == '\'')
			i = handle_q(buf, i);
		else if (buf[i] == '\"')
			i = handle_qq(buf, i);
		else if (buf[i] == '|')
		{
			count++;
			i = handle_pipe(buf, i);
		}
		else if (buf[i] == '>' || buf[i] == '<')
			i = handle_lessgreat(buf, i);
		else
			i++;
	}
	if (split_input(buf, arg, pos, i) <  0)
		return (-1);
	return (0);
}
