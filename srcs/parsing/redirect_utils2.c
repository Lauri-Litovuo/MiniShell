/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:46:11 by aidaneitenb       #+#    #+#             */
/*   Updated: 2024/06/14 21:28:48 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_expand_split(t_shell *arg, char *buf, int i)
{
	while (buf[i] && buf[i] != '\"')
	{
		if (buf[i] == '$')
		{
			arg->split_flag = 1;
			arg->expandrd_flag = 1;
		}
		i++;
	}
	return (i);
}

/****************************************************************
*	Stores an expanded value into rdrct vector					*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	push_rdrct_expand_vector(char *buf, t_shell *arg, size_t pos, int i)
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
	if (vec_push(arg->in[pos]->rdrct, &arg->temp) < 0)
		return (-1);
	check_joinrd(buf, arg, pos, i);
	return (i);
}

int	push_redirect_vector(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->temp = ft_substr(buf, arg->j, (i - arg->j));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-1);
	}
	if (vec_push(arg->in[pos]->rdrct, &arg->temp) < 0)
		return (-1);
	return (i);
}

int	store_specialrd_cmd(char *buf, t_shell *arg, size_t pos, int i)
{
	if (i > arg->j)
	{
		i = push_redirect_vector(buf, arg, pos, i);
		if (i < 0)
			return (-1);
		arg->j = i;
		check_joinrd(buf, arg, pos, i);
	}
	i = push_rdrct_expand_vector(buf, arg, pos, i);
	if (expand_variables(arg, arg->in[pos]->rdrct, \
		arg->in[pos]->rdrct->len - 1) < 0)
		return (-1);
	check_joinrd(buf, arg, pos, i);
	return (i);
}
