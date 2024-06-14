/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:04:40 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/14 21:26:55 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	exclude_quote(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->temp = ft_substr(buf, arg->j + 1, (i - arg->j - 1));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-1);
	}
	if (vec_push(arg->in[pos]->cmd, &arg->temp) < 0)
		return (-1);
	if (arg->expand_flag > 0)
	{
		if (expand_variables(arg, arg->in[pos]->cmd, \
			arg->in[pos]->cmd->len - 1) < 0)
			return (-1);
		arg->expand_flag = 0;
	}
	i++;
	check_join(buf, arg, pos, i);
	return (i);
}

/****************************************************************
*	Stores content between '' into vector. If the str includes	*
*	redirections or $ the quotes will be included in the 		*
*	vector, otherwise the vector saves the content without 		*
*	quotes.														*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_q(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->j = i;
	i++;
	if (buf[i] == '\'')
	{
		i++;
		check_join(buf, arg, pos, i);
		return (i);
	}
	while (buf[i] && buf[i] != '\'')
		i++;
	return (exclude_quote(buf, arg, pos, i));
}

/****************************************************************
*	Stores content between "" into vector. If the str includes	*
*	redirections the quotes will be included in the vector,		*
*	otherwise the vector saves the content without quotes.		*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_qq(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->j = i;
	i++;
	if (buf[i] == '\"')
		return (i + 1);
	while (buf[i] && buf[i] != '\"')
	{
		if (buf[i] == '$')
			arg->expand_flag = 1;
		i++;
	}
	return (exclude_quote(buf, arg, pos, i));
}
