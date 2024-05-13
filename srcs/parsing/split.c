/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:53:19 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/13 12:08:32 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/****************************************************************
*	Stores normal content of buf string into cmd vector.		*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_norm(char *buf, t_shell *arg, size_t pos, int i)
{
	int		j;

	j = i;
	i++;
	while (buf[i] && buf[i] != ' ' && buf[i] != '$' && buf[i] != '<'
		&& buf[i] != '>' && buf[i] != '|' && buf[i] != '\'' && buf[i] != '\"'
		&& buf[i] != '\t' && buf[i] != '\n')
		i++;
	arg->temp = ft_substr(buf, j, (i - j));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].cmd, &arg->temp) < 0)
		return (-2000);
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
	return (0);
}

int	split_input(char *buf, t_shell *arg, size_t pos, int i)
{
	int		j;

	j = 0;
	if (vec_new(&arg[pos].cmd, 1, sizeof(char *)) < 0)
		return (-1);
	if (vec_new(&arg[pos].rdrct, 1, sizeof(char *)) < 0)
		return (-1);
	if (init_vectors(buf, arg, pos, i) == -1)
		return (-1);
	return (0);
}

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
