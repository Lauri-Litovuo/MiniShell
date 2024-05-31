/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:00:48 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/29 15:24:40 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	skip_spaces(char *buf, int i)
{
	while (buf[i] && (buf[i] == ' '
			|| buf[i] == '\t' || buf[i] == '\n'))
		i++;
	return (i);
}

int	handle_start(char *buf, int i)
{
	i = skip_spaces(buf, i);
	if (buf[i] == '|')
	{
		free(buf);
		error_msg(2, SYNTX, "`|'\n");
		return (-2000);
	}
	return (i);
}

int	handle_q(char *buf, int i)
{
	i++;
	if (buf[i] == '\'')
	{
		i++;
		return (i);
	}
	else
	{
		while (buf[i] && (buf[i] != '\''))
			i++;
		if (!buf[i])
		{
			free(buf);
			error_msg(2, UNMATCH, "`''\n");
			return (-2000);
		}
		i++;
		return (skip_spaces(buf, i));
	}
}

int	handle_qq(char *buf, int i)
{
	i++;
	if (buf[i] == '\"')
	{
		i++;
		return (i);
	}
	else
	{
		while (buf[i] && buf[i] != '\"')
			i++;
		if (!buf[i])
		{
			free(buf);
			error_msg(2, UNMATCH, "`\"'\n");
			return (-2000);
		}
		i++;
		return (skip_spaces(buf, i));
	}
}

int	handle_pipe(char *buf, int i)
{
	i++;
	if (buf[i] == '|')
	{
		free(buf);
		error_msg(2, SYNTX, "`|'\n");
		return (-2000);
	}
	i = skip_spaces(buf, i);
	if (buf[i] == '\0')
	{
		free(buf);
		error_msg(2, SYNTX, "`newline'\n");
		return (-2000);
	}
	if (buf[i] == '|')
	{
		free(buf);
		error_msg(2, SYNTX, "`|'\n");
		return (-2000);
	}
	return (i);
}
