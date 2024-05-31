/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:04:40 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/31 12:15:50 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exclude_quote(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->temp = ft_substr(buf, arg->j + 1, (i - arg->j - 1));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL); //do I need to free buf? maybe in bigger parse
		return (-2000);
	}
	if (vec_push(&arg[pos].cmd, &arg->temp) < 0)
		return (-2000);
	if (arg->expand_flag > 0)
	{
		if (expand_variables(&arg->env, &arg[pos].cmd, \
			arg[pos].cmd.len - 1) < 0)
			return (-1);
		arg->expand_flag = 0;
	}
	i++;
	check_join(buf, arg, pos, i);
	return (i);
}

int	include_quote(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->temp = ft_substr(buf, arg->j, (i - arg->j + 1));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].cmd, &arg->temp) < 0)
		return (-2000);
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
	int	flag;

	flag = 0;
	arg->j = i;
	i++;
	if (buf[i] == '\'')
	{
		i++;
		check_join(buf, arg, pos, i);
		return (i);
	}
	while (buf[i] && buf[i] != '\'')
	{
		if (buf[i] == '>' || buf[i] == '<')
			flag = 1;
		i++;
	}
	if (flag == 1)
		return (include_quote(buf, arg, pos, i));
	else
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
	int	flag;

	flag = 0;
	arg->j = i;
	i++;
	if (buf[i] == '\"')
		return (i + 1);
	while (buf[i] && buf[i] != '\"')
	{
		if (buf[i] == '>' || buf[i] == '<')
			flag = 1;
		if (buf[i] == '$')
			arg->expand_flag = 1;
		i++;
	}
	if (flag == 1)
		return (include_quote(buf, arg, pos, i));
	else
		return (exclude_quote(buf, arg, pos, i));
}
