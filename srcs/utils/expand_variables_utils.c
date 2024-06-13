/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:01:04 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/13 11:32:24 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	expand_to_env_var(t_shell *arg, t_expd *s, t_vec *vec, int index)
{
	char	*dupped;

	s->expanded = malloc (ft_strlen(*(char **)vec_get(&arg->env, s->var_index)) \
	- s->var_len);
	if (!s->expanded)
		return (-1);
	s->exp_len = ft_strlcpy(s->expanded, \
	(*(char **)vec_get(&arg->env, s->var_index) + s->var_len + 1), PATH_MAX);
	s->new = ft_substr(s->str, 0, s->pre_len);
	if (!s->new)
		return (-1);
	s->join = ft_strjoin(s->new, s->expanded);
	free(s->new);
	s->new = ft_substr(s->str, (s->ds + s->var_len + 1), ft_strlen(s->str));
	free(s->expanded);
	dupped = ft_strjoin(s->join, s->new);
	free(s->new);
	free(s->join);
	vec_replace_str(vec, dupped, index);
	return (0);
}

int	expand_to_empty(t_expd *s, t_vec *vec, int index)
{
	char	*dupped;

	s->new = malloc((s->total_len - s->var_len + 1) * 1);
	s->new = ft_substr(s->str, 0, s->pre_len);
	ft_strlcat(s->new, s->str + (s->ds + s->var_len), \
	(s->total_len - s->var_len + s->exp_len));
	if (!s->new)
		return (-1);
	dupped = ft_strdup(s->new);
	if (!dupped)
		return (-1);
	vec_replace_str(vec, dupped, index);
	return (0);
}

int	expand_to_exit_status(t_shell *arg, t_expd *s, t_vec *vec, int index)
{
	char	*dupped;

	s->expanded = ft_itoa(arg->exit_code);
	if (s->expanded == NULL)
		return (-1);
	s->exp_len = ft_strlen(s->expanded);
	s->new = malloc((s->total_len - 2 + s->exp_len) * 1);
	if (!s->new)
		return (-1);
	s->new = ft_substr(s->str, 0, s->pre_len);
	if (!s->new)
		return (-1);
	s->join = ft_strjoin(s->new, s->expanded);
	free(s->new);
	s->new = ft_substr(s->str, (s->ds + 2), ft_strlen(s->str));
	free(s->expanded);
	dupped = ft_strjoin(s->join, s->new);
	free(s->new);
	free(s->join);
	vec_replace_str(vec, dupped, index);
	return (0);
}
