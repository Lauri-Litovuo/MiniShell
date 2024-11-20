/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:03:03 by aidaneitenb       #+#    #+#             */
/*   Updated: 2024/11/20 14:13:42 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	join_vecrd_strs(t_shell *arg, size_t pos, t_vecjoin *s)
{
	int	flag;

	flag = 0;
	arg->joinrd_flag++;
	while (arg->joinrd_flag < arg->endrd_flag)
	{
		flag++;
		if (s->fin)
			free(s->fin);
		s->fin = ft_strjoin(s->base, \
			*(char **)vec_get(arg->in[pos]->rdrct, arg->joinrd_flag));
		if (flag > 1)
			free(s->base);
		s->base = ft_strdup(s->fin);
		if (s->base == NULL)
			return (-1);
		arg->joinrd_flag++;
	}
	free(s->base);
	return (0);
}

static int	join_vec_strs(t_shell *arg, size_t pos, t_vecjoin *s)
{
	int	flag;

	flag = 0;
	arg->join_flag++;
	while (arg->join_flag < arg->end_flag)
	{
		flag++;
		if (s->fin)
			free(s->fin);
		s->fin = ft_strjoin(s->base, \
			*(char **)vec_get(arg->in[pos]->cmd, arg->join_flag));
		if (flag > 1)
			free(s->base);
		s->base = ft_strdup(s->fin);
		if (s->base == NULL)
			return (-1);
		arg->join_flag++;
	}
	free(s->base);
	return (0);
}

static int	join_rdrct_vector(t_shell *arg, size_t pos, t_vecjoin *s)
{
	int	i;

	s->index = arg->joinrd_flag;
	i = s->index + 1;
	s->base = *(char **)vec_get(arg->in[pos]->rdrct, arg->joinrd_flag);
	if (join_vecrd_strs(arg, pos, s) < 0)
		return (-1);
	if (vec_replace_special(arg->in[pos]->rdrct, s->fin, (size_t)s->index) < 0)
		return (-1);
	s->index++;
	while (s->index < arg->endrd_flag)
	{
		vec_remove_str(arg->in[pos]->rdrct, i);
		s->index++;
	}
	return (0);
}

static int	join_cmd_vector(t_shell *arg, size_t pos, t_vecjoin *s)
{
	int	i;

	s->index = arg->join_flag;
	i = s->index + 1;
	s->base = *(char **)vec_get(arg->in[pos]->cmd, arg->join_flag);
	if (join_vec_strs(arg, pos, s) < 0)
		return (-1);
	if (vec_replace_special(arg->in[pos]->cmd, s->fin, (size_t)s->index) < 0)
		return (-1);
	s->index++;
	while (s->index < arg->end_flag)
	{
		vec_remove_str(arg->in[pos]->cmd, i);
		s->index++;
	}
	return (0);
}

int	vec_join(t_shell *arg, size_t pos)
{
	t_vecjoin	s;
	int			ret;

	init_s(&s);
	(void) ret;
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
