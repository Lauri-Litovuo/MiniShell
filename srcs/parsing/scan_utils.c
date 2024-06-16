/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:00:48 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/16 12:07:00 by aneitenb         ###   ########.fr       */
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
		return (-1);
	}
	else if ((buf[i] == '\'' && buf[i + 1] == '\'')
		|| (buf[i] == '\"' && buf[i + 1] == '\"'))
	{
		i += 2;
		i = skip_spaces(buf, i);
		if (buf[i])
			return (i);
		else
		{
			free(buf);
			error_msg(1, CMD, NULL);
			return (-1);
		}
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
			return (-1);
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
			return (-1);
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
		return (-1);
	}
	i = skip_spaces(buf, i);
	if (buf[i] == '\0')
	{
		free(buf);
		error_msg(2, SYNTX, "`newline'\n");
		return (-1);
	}
	if (buf[i] == '|')
	{
		free(buf);
		error_msg(2, SYNTX, "`|'\n");
		return (-1);
	}
	return (i);
}
