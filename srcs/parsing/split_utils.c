/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidaneitenbach <aidaneitenbach@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:17:08 by aidaneitenb       #+#    #+#             */
/*   Updated: 2024/05/19 21:24:41 by aidaneitenb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	check_join(char *buf, t_shell *arg, size_t pos, int i)
{
    if (arg->join_flag > -1 && (!buf[i] || buf[i] == ' ' || buf[i] == '\t' || \
		buf[i] == '\n' || buf[i] == '<' || buf[i] == '>' || buf[i] == '|'))
		arg->end_flag = arg[pos].cmd.len;
	if (arg->join_flag == -1 && buf[i] && buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n'
		&& buf[i] != '<' && buf[i] != '>' && buf[i] != '|')
		{
			printf("arg.cmd.len: %zu\n", arg[pos].cmd.len);
			arg->join_flag = arg[pos].cmd.len - 1;
		}
}

void	check_joinrd(char *buf, t_shell *arg, size_t pos, int i)
{
    if (arg->joinrd_flag > -1 && (!buf[i] || buf[i] == ' ' || buf[i] == '\t' || \
		buf[i] == '\n' || buf[i] == '<' || buf[i] == '>' || buf[i] == '|'))
		arg->endrd_flag = arg[pos].rdrct.len;
	if (arg->joinrd_flag == -1 && buf[i] && buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\n'
		&& buf[i] != '<' && buf[i] != '>' && buf[i] != '|')
		arg->joinrd_flag = arg[pos].rdrct.len - 1;
}

int	push_expand_vector(char *buf, t_shell *arg, size_t pos, int i)
{
	i++;
	while (buf[i] && buf[i] != ' ' && buf[i] != '$' && buf[i] != '<'
		&& buf[i] != '>' && buf[i] != '|' && buf[i] != '\'' 
		&& buf[i] != '\"' && buf[i] != '\t' && buf[i] != '\n')
		i++;
    check_join(buf, arg, pos, i);
	arg->temp = ft_substr(buf, arg->j, (i - arg->j));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-1);
	}
	if (vec_push(&arg[pos].cmd, &arg->temp) < 0)
		return (-1);
	return (i);
}

int	push_to_vector(char *buf, t_shell *arg, size_t pos, int i)
{
	arg->temp = ft_substr(buf, arg->j, (i - arg->j));
	if (arg->temp == NULL)
	{
		error_msg(1, SUBSTR, NULL);
		return (-1);
	}
	if (vec_push(&arg[pos].cmd, &arg->temp) < 0)
		return (-1); 
	return (i);
}