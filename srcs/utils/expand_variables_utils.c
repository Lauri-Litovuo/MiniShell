/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:01:04 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/16 12:28:00 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	expand_to_env_var(t_shell *arg, t_expd *s, t_vec *vec, int index)
{
	char	*dupped;
	char	*remove;

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
	free(s->expanded);
	s->new = ft_substr(s->str, (s->ds + s->var_len + 1), ft_strlen(s->str));
	dupped = ft_strjoin(s->join, s->new);
	free(s->new);
	free(s->join);
	remove = *(char **)vec_get(vec, index);
	vec_replace_str(vec, dupped, index);
	free(remove);
	return (0);
}

int	expand_to_empty(t_expd *s, t_vec *vec, int index)
{
	char	*dupped;
	char	*remove;

	if (s->pre_len != 0 && s->total_len - s->var_len != 0)
	{
		s->new = ft_substr(s->str, 0, s->pre_len);
		if (!s->new)
			return (-1);
		ft_strlcat(s->new, s->str + (s->ds + s->var_len), \
		(s->total_len - s->var_len));
		if (!s->new)
			return (-1);
		dupped = ft_strdup(s->new);
		free (s->new);
	}
	else
		dupped = ft_strdup("\0");
	if (!dupped)
		return (-1);
	remove = *(char **)vec_get(vec, index);
	vec_replace_str(vec, dupped, index);
	free(remove);
	return (0);
}

int	expand_to_exit_status(t_shell *arg, t_expd *s, t_vec *vec, int index)
{
	char	*dupped;
	char	*remove;

	s->expanded = ft_itoa(arg->exit_code);
	if (s->expanded == NULL)
		return (-1);
	s->exp_len = ft_strlen(s->expanded);
	s->new = ft_substr(s->str, 0, s->pre_len);
	if (!s->new)
		return (free(s->expanded), -1);
	s->join = ft_strjoin(s->new, s->expanded);
	free(s->new);
	free(s->expanded);
	s->new = ft_substr(s->str, (s->ds + 2), ft_strlen(s->str));
	if (!s->new)
		return (free(s->join), -1);
	dupped = ft_strjoin(s->join, s->new);
	free(s->new);
	free(s->join);
	remove = *(char **)vec_get(vec, index);
	if (!dupped || !remove)
		return (-1);
	vec_replace_str(vec, dupped, index);
	free(remove);
	return (0);
}

void	get_count(t_vec *vec, int index, t_expd *s)
{
	size_t	i;
	char	*str;

	i = 0;
	str = *(char **)vec_get(vec, index);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			s->count++;
		i++;
	}
}

void	handle_expand(t_shell *arg, t_expd *s, t_vec *vec, int index)
{
	s->count--;
	s->pre_len = s->ds;
	if (s->str[s->ds] == '$' && s->str[s->ds + 1] == '?')
		s->ret = expand_to_exit_status(arg, s, vec, index);
	else
		s->ret = expand_string(arg, s, vec, index);
}
