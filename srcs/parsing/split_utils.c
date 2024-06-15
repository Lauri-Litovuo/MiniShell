/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:17:08 by aidaneitenb       #+#    #+#             */
/*   Updated: 2024/06/15 16:53:13 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/************************************************************
*	Stores expandable content of buf string, possibly		*
*	following normal characters, into single vector.		*
*	Returns: placement of i within the buf string.			*
*************************************************************/
int	store_special_cmd(char *buf, t_shell *arg, size_t pos, int i)
{
	if (i > arg->j)
	{
		i = push_to_vector(buf, arg, pos, i);
		if (i < 0)
			return (-1);
		arg->j = i;
		check_join(buf, arg, pos, i);
	}
	i = push_expand_vector(buf, arg, pos, i);
	if (expand_variables(arg, arg->in[pos]->cmd, \
		arg->in[pos]->cmd->len - 1) < 0)
		return (-1);
	check_join(buf, arg, pos, i);
	return (i);
}

void	check_join(char *buf, t_shell *arg, size_t pos, int i)
{
	if (arg->join_flag > -1 && arg->end_flag == 0 && (!buf[i] || buf[i] == ' ' \
		|| buf[i] == '\t' || buf[i] == '\n' || buf[i] == '<' || buf[i] == '>' \
		|| buf[i] == '|'))
		arg->end_flag = arg->in[pos]->cmd->len;
	if (arg->join_flag == -1 && buf[i] && buf[i] != ' ' && buf[i] != '\t' \
		&& buf[i] != '\n' && buf[i] != '<' && buf[i] != '>' && buf[i] != '|')
		arg->join_flag = arg->in[pos]->cmd->len - 1;
}

void	check_joinrd(char *buf, t_shell *arg, size_t pos, int i)
{
	if (arg->joinrd_flag > -1 && arg->endrd_flag == 0 && (!buf[i] \
		|| buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n' || buf[i] == '<' \
		|| buf[i] == '>' || buf[i] == '|'))
		arg->endrd_flag = arg->in[pos]->rdrct->len;
	if (arg->joinrd_flag == -1 && buf[i] && buf[i] != ' ' && buf[i] != '\t' \
		&& buf[i] != '\n' && buf[i] != '<' && buf[i] != '>' && buf[i] != '|')
		arg->joinrd_flag = arg->in[pos]->rdrct->len - 1;
}

int	push_expand_vector(char *buf, t_shell *arg, size_t pos, int i)
{
	i++;
	while (buf[i] && buf[i] != ' ' && buf[i] != '$' && buf[i] != '<' \
		&& buf[i] != '>' && buf[i] != '|' && buf[i] != '\'' \
		&& buf[i] != '\"' && buf[i] != '\t' && buf[i] != '\n')
		i++;
	arg->temp = ft_substr(buf, arg->j, (i - arg->j));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-1);
	}
	if (vec_push(arg->in[pos]->cmd, &arg->temp) < 0)
		return (-1);
	return (i);
}

int	push_to_vector(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->temp = ft_substr(buf, arg->j, (i - arg->j));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-1);
	}
	if (vec_push(arg->in[pos]->cmd, &arg->temp) < 0)
		return (-1);
	return (i);
}
