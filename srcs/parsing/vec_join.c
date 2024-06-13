/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:03:03 by aidaneitenb       #+#    #+#             */
/*   Updated: 2024/06/13 20:27:17 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	reset_flags(t_shell *arg)
{
	arg->join_flag = -1;
	arg->end_flag = 0;
	arg->joinrd_flag = -1;
	arg->endrd_flag = 0;
	arg->expand_flag = 0;
}

void	init_s(t_vecjoin *s)
{
	s->base = NULL;
	s->fin = NULL;
	s->index = 0;
}

int	join_rdrct_vector(t_shell *arg, size_t pos, t_vecjoin *s)
{
	int	i;
	int	flag;

	flag = 0;
	s->index = arg->joinrd_flag;
	i = s->index + 1;
	s->base = *(char **)vec_get(&arg[pos].rdrct, arg->joinrd_flag);
	arg->joinrd_flag++;
	while (arg->joinrd_flag < arg->endrd_flag)
	{
		flag++;
		if (s->fin)
			free(s->fin);
		s->fin = ft_strjoin(s->base, \
			*(char **)vec_get(&arg[pos].rdrct, arg->joinrd_flag));
		if (flag > 1)
			free(s->base);
		s->base = ft_strdup(s->fin);
		if (s->base == NULL)
			return (-1);
		arg->joinrd_flag++;
	}
	free(s->base);
	if (vec_replace_special(&arg[pos].rdrct, s->fin, (size_t)s->index) < 0)
		return (-1);
	s->index++;
	while (s->index < arg->endrd_flag)
	{
		vec_remove_str(&arg[pos].rdrct, i);
		s->index++;
	}
	return (0);
}

int	join_cmd_vector(t_shell *arg, size_t pos, t_vecjoin *s)
{
	int	i;
	int	flag;

	flag = 0;
	s->index = arg->join_flag;
	i = s->index + 1;
	s->base = *(char **)vec_get(&arg[pos].cmd, arg->join_flag);
	arg->join_flag++;
	while (arg->join_flag < arg->end_flag)
	{
		if (s->fin)
			free(s->fin);
		s->fin = ft_strjoin(s->base, \
			*(char **)vec_get(&arg[pos].cmd, arg->join_flag));
		if (flag > 1)
			free(s->base);
		s->base = ft_strdup(s->fin);
		if (s->base == NULL)
			return (-1);
		arg->join_flag++;
	}
	free(s->base);
	if (vec_replace_special(&arg[pos].cmd, s->fin, (size_t)s->index) < 0)
		return (-1);
	s->index++;
	while (s->index < arg->end_flag)
	{
		vec_remove_str(&arg[pos].cmd, i);
		s->index++;
	}
	return (0);
}

int	vec_join(t_shell *arg, size_t pos)
{
	t_vecjoin	s;
	int			ret;

	init_s(&s);
	if (arg->join_flag > -1)
	{
		ret = join_cmd_vector(arg, pos, &s);
		init_s(&s);
	}
	if (arg->joinrd_flag > -1)
	{
		ret = join_rdrct_vector(arg, pos, &s);
		init_s(&s);
	}
	reset_flags(arg);
	return (0);
}
