/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:01:04 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/12 16:23:04 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	expand_to_env_var(t_vec *env, t_expd *s, t_vec *vec)
{
	char	*dupped;
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
	ft_strlcat(s->new, s->str + s->ds + s->var_len, \
	(s->total_len - s->var_len + s->exp_len));
	if (!s->new)
		return (-1);
	dupped = ft_strdup(s->new);
	if (!dupped)
		return (-1);
	vec_replace_str(vec, dupped, s->index);
	return (0);
}

int	get_pid(char *expand)
{
	expand = ft_strdup("12312"); //arb value, make better
	return (0);
}


int	get_exit_status(s.expanded);

void	free_expd(t_expd *s)
{
	if (s->temp)
		free (s->temp);
	if (s->str)
		free (s->str);
	if (s->expanded)
		free (s->expanded);
	if (s->env_var)
		fre (s->env_var);
	if (s->new)
		free (s->new);
}

