/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:46:11 by aidaneitenb       #+#    #+#             */
/*   Updated: 2024/05/21 13:45:29 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
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
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
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
	if (expand_variables(&arg->env, &arg[pos].rdrct, \
		arg[pos].rdrct.len - 1) < 0)
		return (-1);
	check_joinrd(buf, arg, pos, i);
	return (i);
}
