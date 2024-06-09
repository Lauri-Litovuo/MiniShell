/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:39:34 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/07 15:42:26 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	last_red_error(char *buf, int i)
{
	if (buf[i + 1] == '<')
	{
		if (buf[i + 2] == '<')
		{
			free(buf);
			error_msg(2, SYNTX, "`<<<'\n");
			return (-2000);
		}
		free(buf);
		error_msg(2, SYNTX, "`<<'\n");
		return (-2000);
	}
	if (buf[i + 1] == '>')
	{
		free(buf);
		error_msg(2, SYNTX, "`<>'\n");
		return (-2000);
	}
	return (i);
}

static int	redirect_error(char *buf, int i)
{
	if (buf[i] == '>')
	{
		if (buf[i + 1] == '>')
		{
			free(buf);
			error_msg(2, SYNTX, "`>>'\n");
			return (-2000);
		}
		free(buf);
		error_msg(2, SYNTX, "`>'\n");
		return (-2000);
	}
	if (buf[i] == '<')
		return (last_red_error(buf, i));
	return (i);
}

static int	check_endofinput(char *buf, int i)
{
	int	ret;

	ret = i;
	if (!buf[i])
	{
		free(buf);
		error_msg(2, SYNTX, "`newline'\n");
		return (-2000);
	}
	else if (buf[i] == '|')
	{
		free(buf);
		error_msg(2, SYNTX, "`|'\n");
		return (-2000);
	}
	else if (buf[i] == '>' || buf[i] == '<')
		return (redirect_error(buf, i));
	else
		return (ret);
}

static int	handle_great(char *buf, int i)
{
	if (buf[i] == '>')
	{
		i++;
		if (buf[i] == '>')
		{
			i++;
			if (buf[i] == '<' || buf[i] == '>')
			{
				error_msg(2, SYNTX, "`>'\n");
				return (-1);
			}
		}
		else if (buf[i] == '<')
		{
			free(buf);
			error_msg(2, SYNTX, "`<'\n");
			return (-1);
		}
	}
	i = skip_spaces(buf, i);
	return (check_endofinput(buf, i));
}

int	handle_lessgreat(char *buf, int i)
{
	int	count;

	count = i;
	if (buf[i] == '>')
		return (handle_great(buf, i));
	if (buf[i] == '<')
	{
		i++;
		if (buf[i] == '<' || buf[i] == '>')
		{
			i++;
			if (buf[i] == '<' || buf[i] == '>')
			{
				error_msg(2, SYNTX, "`newline'\n");
				return (-1);
			}
			if (buf[i] == '>')
			{
				error_msg(2, SYNTX, "`>'\n");
				return (-1);
			}
		}
	}
	i = skip_spaces(buf, i);
	return (check_endofinput(buf, i));
}
