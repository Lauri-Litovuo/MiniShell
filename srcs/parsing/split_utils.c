/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:47:25 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/11 18:53:16 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/****************************************************************
*	Stores < or > redirection into vector						*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_single(char *buf, t_shell *arg, size_t pos, int i, int j)
{
	arg->temp = ft_substr(buf, j, 1);
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
		return (-2000);
	return (i);
}

/****************************************************************
*	Stores << or >> redirection into vector						*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_double(char *buf, t_shell *arg, size_t pos, int i, int j)
{
	arg->temp = ft_substr(buf, j, 2);
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
		return (-2000);
	i++;
	return (i);
}

/****************************************************************
*	Stores file content within "" into rdrct vector				*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	rdrct_qq(char *buf, t_shell *arg, size_t pos, int i, int j)
{
	i++;
	while (buf[i] && buf[i] != '\"')
		i++;
	arg->temp = ft_substr(buf, j + 1, (i - j - 1));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
		return (-2000);
	return (i);
}

/****************************************************************
*	Stores file content within '' into rdrct vector				*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	rdrct_q(char *buf, t_shell *arg, size_t pos, int i, int j)
{
	i++;
	while (buf[i] && buf[i] != '\'')
		i++;
	arg->temp = ft_substr(buf, j + 1, (i - j - 1));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
		return (-2000);
	return (i);
}

/****************************************************************
*	Stores file name into rdrct vector							*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	rdrct_file(char *buf, t_shell *arg, size_t pos, int i, int j)
{
	while (buf[i] && buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n'
		&& buf[i] != '|' && buf[i] != '>' && buf[i] != '<')
		i++;
	arg->temp = ft_substr(buf, j, (i - j + 1));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-2000);
	}
	if (vec_push(&arg[pos].rdrct, &arg->temp) < 0)
		return (-2000);
	return (i);
}