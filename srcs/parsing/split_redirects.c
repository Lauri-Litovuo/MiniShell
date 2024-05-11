/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:09:17 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/11 18:56:02 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/****************************************************************
*	Stores < or << redirection and its following file.			*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_less(char *buf, t_shell *arg, size_t pos, int i)
{
	int	j;

	j = i;
	i++;
	if (buf[i] == '<')
		i = store_double(buf, arg, pos, i, j);
	else
		i = store_single(buf, arg, pos, i, j);
	i = skip_spaces(buf, i);
	j = i;
	if (buf[i] == '\'')
		i = rdrct_q(buf, arg, pos, i, j);
	else if (buf[i] == '\"')
		i = rdrct_qq(buf, arg, pos, i, j);
	else
		i = rdrct_file(buf, arg, pos, i, j);
	return (i);
}

/****************************************************************
*	Stores > or >> redirection and its following file.			*
*	Returns: placement of i within the buf string.				*
*****************************************************************/
int	store_great(char *buf, t_shell *arg, size_t pos, int i)
{
	int	j;

	j = i;
	i++;
	if (buf[i] == '>')
		i = store_double(buf, arg, pos, i, j);
	else
		i = store_single(buf, arg, pos, i, j);
	i = skip_spaces(buf, i);
	j = i;
	if (buf[i] == '\'')
		i = rdrct_q(buf, arg, pos, i, j);
	else if (buf[i] == '\"')
		i = rdrct_qq(buf, arg, pos, i, j);
	else
		i = rdrct_file(buf, arg, pos, i, j);
	return (i);
}