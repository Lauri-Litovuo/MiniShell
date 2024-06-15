/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:53:19 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/15 16:53:29 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
		if (arg->end_flag > 0 || arg->endrd_flag > 0)
			if (vec_join(arg, arg->i) < 0)
				return (-1);
		arg->i++;
	}
	return (0);
}

/****************************************************************
*	Stores normal content of buf string into cmd vector.		*
*	Also checks for longline content and joins the vector 		*
*	pointers into one long vector  pointer in that case.		*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_norm(char *buf, t_shell *arg, size_t pos, int i)
{
	if (!buf[i])
		return (i);
	arg->j = i;
	while (buf[i] && buf[i] != ' ' && buf[i] != '$' && buf[i] != '<'
		&& buf[i] != '>' && buf[i] != '|' && buf[i] != '\'' && buf[i] != '\"'
		&& buf[i] != '\t' && buf[i] != '\n')
		i++;
	if (buf[i] == '$')
	{
		arg->split_flag = 1;
		i = store_special_cmd(buf, arg, pos, i);
	}
	else
	{
		arg->temp = ft_substr(buf, arg->j, (i - arg->j));
		if (arg->temp == NULL)
		{
			error_msg(1, SUBSTR, NULL);
			return (-1);
		}
		if (vec_push(arg->in[pos]->cmd, &arg->temp) < 0)
			return (-1);
		check_join(buf, arg, pos, i);
	}
	return (i);
}

int	init_vectors(char *buf, t_shell *arg, size_t pos, int i)
{
	while (buf[i])
	{
		i = skip_spaces(buf, i);
		if (buf[i] == '|')
			return (0);
		else if (buf[i] == '\'')
			i = store_q(buf, arg, pos, i);
		else if (buf[i] == '\"')
			i = store_qq(buf, arg, pos, i);
		else if (buf[i] == '<')
			i = store_less(buf, arg, pos, i);
		else if (buf[i] == '>')
			i = store_great(buf, arg, pos, i);
		else
			i = store_norm(buf, arg, pos, i);
		if (i < 0)
			return (-1);
	}
	if (i < 0)
		return (-1);
	if (i >= PATH_MAX)
		return (-1);
	return (0);
}

/****************************************************************
*	Creates vectors for each new arg->count depending on		*
*	what position is passed as a parameter.						*
*	Returns: -1 on error.										*
*****************************************************************/
int	split_input(char *buf, t_shell *arg, size_t pos, int i)
{
	if (vec_new(arg->in[pos]->cmd, 10, sizeof(char *)) < 0)
		return (-1);
	if (vec_new(arg->in[pos]->rdrct, 10, sizeof(char *)) < 0)
		return (-1);
	if (init_vectors(buf, arg, pos, i) == -1)
		return (-1);
	return (0);
}

/****************************************************************
*	Finds the index of starting point within buf string, 		*
*	depending on which arg->count was passed as pos.			*
*	Returns: -1 on error.										*
*****************************************************************/
int	split_rest(char *buf, t_shell *arg, size_t pos)
{
	size_t	count;
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
	if (split_input(buf, arg, pos, i) < 0)
		return (-1);
	return (0);
}
