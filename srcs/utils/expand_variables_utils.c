/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:01:04 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/13 11:49:09 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	expand_to_env_var(t_vec *env, t_expd *s, t_vec *vec)
{
	char	*dupped;

	s->expanded = malloc (ft_strlen(*(char **)vec_get(env, s->var_index)) \
	- s->var_len - 1);
	ft_strlcpy(s->expanded, \
	(*(char **)vec_get(env, s->var_index) + s->var_len + 1), PATH_MAX);
	s->exp_len = ft_strlen(s->expanded);
	s->new = malloc((s->total_len - s->var_len + s->exp_len) * 1);
	s->new = ft_substr(s->str, 0, s->pre_len);
	if (!s->new)
		return (-1);
	ft_strlcat(s->new, s->expanded, (s->total_len - s->var_len + s->exp_len));
	if (!s->new)
		return (-1);
	ft_strlcat(s->new, s->str + (s->ds + s->var_len), \
	(s->total_len - s->var_len + s->exp_len));
	if (!s->new)
		return (-1);
	dupped = ft_strdup(s->new);
	if (!dupped)
		return (-1);
	vec_replace_str(vec, dupped, s->index);
	return (0);
}

int	expand_to_empty(t_expd *s, t_vec *vec)
{
	char	*dupped;

	s->new = malloc((s->total_len - s->var_len) * 1);
	s->new = ft_substr(s->str, 0, s->pre_len);
	ft_strlcat(s->new, s->str + (s->ds + s->var_len), \
	(s->total_len - s->var_len + s->exp_len));
	if (!s->new)
		return (-1);
	dupped = ft_strdup(s->new);
	if (!dupped)
		return (-1);
	vec_replace_str(vec, dupped, s->index);
	return (0);
}

int	expand_to_exit_status(t_expd *s, t_vec *vec)
{
	char	*dupped;

	s->exp_len = ft_strlen(s->expanded);
	s->expanded = ft_itoa(g_exit_status);
	s->exp_len = ft_strlen(s->expanded);
	s->new = malloc((s->total_len + s->exp_len - 2) * 1);
	s->new = ft_substr(s->str, 0, s->pre_len);
	if (!s->new)
		return (-1);
	ft_strlcat(s->new, s->expanded, (s->total_len + s->exp_len - 2));
	if (!s->new)
		return (-1);
	ft_strlcat(s->new, s->str + (s->ds + 2), \
	(s->total_len + s->exp_len - 2));
	if (!s->new)
		return (-1);
	dupped = ft_strdup(s->new);
	if (!dupped)
		return (-1);
	vec_replace_str(vec, dupped, s->index);
	s->str = *(char **)vec_get(vec, s->index);
	return (0);
}

void	free_expd(t_expd *s)
{
	if (s->temp)
		free (s->temp);
	if (s->str)
		free (s->str);
	if (s->expanded)
		free (s->expanded);
	if (s->env_var)
		free (s->env_var);
	if (s->new)
		free (s->new);
	s->var_len = 0;
	s->exp_len = 0;
	s->i = 0;
	s->ret = 0;
	s->temp = NULL;
	s->str = NULL;
	s->expanded = NULL;
	s->env_var = NULL;
	s->new = NULL;
}

