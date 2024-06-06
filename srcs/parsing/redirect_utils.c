/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:47:25 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/06 15:51:05 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/****************************************************************
*	Stores < or > redirection into vector						*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_single(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->temp = ft_substr(buf, arg->j, 1);
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
		return (-2000);
	return (i + 1);
}

/****************************************************************
*	Stores << or >> redirection into vector						*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_double(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->temp = ft_substr(buf, arg->j, 2);
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
		return (-2000);
	return (i + 2);
}

/****************************************************************
*	Stores file content within "" into rdrct vector				*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	rdrct_qq(char *buf, t_shell *arg, size_t pos, int i)
{
	i++;
	while (buf[i] && buf[i] != '\"')
	{
		if (buf[i] == '$')
		{
			arg->split_flag = 1;
			arg->expandrd_flag = 1;
		}
		i++;
	}
	arg->temp = ft_substr(buf, arg->j + 1, (i - arg->j - 1));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
		return (-2000);
	if (arg->expandrd_flag > 0)
	{
		if (expand_variables(arg->exit_code, &arg->env, &arg[pos].rdrct, \
			arg[pos].rdrct.len - 1) < 0)
			return (-1);
	}
	i++;
	check_joinrd(buf, arg, pos, i);
	return (i);
}

/****************************************************************
*	Stores file content within '' into rdrct vector				*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	rdrct_q(char *buf, t_shell *arg, size_t pos, int i)
{
	i++;
	while (buf[i] && buf[i] != '\'')
		i++;
	arg->temp = ft_substr(buf, arg->j + 1, (i - arg->j - 1));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
		return (-2000);
	i++;
	check_joinrd(buf, arg, pos, i);
	return (i);
}

/****************************************************************
*	Stores file name into rdrct vector							*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	rdrct_file(char *buf, t_shell *arg, size_t pos, int i)
{
	while (buf[i] && buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n'
		&& buf[i] != '|' && buf[i] != '>' && buf[i] != '<' && buf[i] != '$'
		& buf[i] != '\'' & buf[i] != '\"')
		i++;
	if (buf[i] == '$')
	{
		arg->split_flag = 1;	
		i = store_specialrd_cmd(buf, arg, pos, i);
	}
	else
	{
		arg->temp = ft_substr(buf, arg->j, (i - arg->j));
		if (arg->temp == NULL)
		{
			error_msg(1, SUBSTR, NULL);
			return (-2000);
		}
		if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
			return (-2000);
		check_joinrd(buf, arg, pos, i);
	}
	return (i);
}
