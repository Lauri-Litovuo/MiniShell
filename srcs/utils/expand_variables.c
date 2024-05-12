/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:44:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/12 16:20:01 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	expand_variables(t_vec *env, t_shell *arg)
{
	if (&arg->cmd.len != 0)
	{
		if (expand_cmd_and_rdrct(env, &arg->cmd) < 0)
			return (-1);
	}
	if (&arg->rdrct.len != 0)
	{
		if (expand_cmd_and_rdrct(env, &arg->rdrct) < 0)
			return (-1);
	}
}

int	expand_cmd_and_rdrct(t_vec *env, t_vec *vec)
{
	t_expd	s;

	init_expd_struct(&s);
	while (s.index < vec->len)
	{
		s.str = *(char **)vec_get(vec, s.index);
		s.total_len = ft_strlen(s.str);
		while (s.str[s.ds] != '\0')
		{
			if (s.str[s.ds] == '$')
				s.pre_len = s.ds;
			else if (s.str[s.ds] == '$' && s.str[s.ds + 1] == '$')
				s.ret = get_pid(s.expanded);
			else if (s.str[s.ds] == '$' && s.str[s.ds + 1] == '?')
				s.ret = get_exit_status(s.expanded);
			else if (s.str[s.ds] == '$')
				s.ret = expand_string(env, &s, vec);
			if (s.ret < 0)
				return (-1);
			s.ds++;
		}
		s.index++;
	}
	free_expd(&s);
	return (0);
}

static void	init_expd_struct(t_expd *s)
{
	s->temp = NULL;
	s->str = NULL;
	s->expanded = NULL;
	s->var_len = 0;
	s->exp_len = 0;
	s->i = 0;
	s->ret = 0;
	s->index = 0;
}

int	expand_string(t_vec *env, t_expd *s, t_vec *vec)
{
	s->ret = check_if_exists(env, &s);
	if (s->ret > 0)
	{
		if (expand_to_env_var(env, s, vec) < 0)
			return (-1);
	}
	else if (s->ret < 0)
		return (-1);
}

int	check_if_exists(t_vec *env, t_expd *s)
{
	s->i = s->ds + 1;
	while (s->str[s->i] && \
	(ft_isalnum(s->str[s->i]) != 0 || s->str[s->i] == '_'))
		s->i++;
	s->var_len = s->i - s->ds;
	s->env_var = ft_substr(s->str, s->ds + 1, s->i);
	if (!s->env_var)
		return (-1);
	s->var_index = 0;
	while (s->var_index < env->len)
	{
		s->temp = extract_env_var(*(char **)vec_get(env, s->var_index));
		if (s->temp == NULL)
			return (-1);
		if (ft_strncmp(s->temp, s->env_var, s->var_len) == 0
			&& s->temp[s->var_len + 1] == '=')
			return (1);
		free (s->temp);
		s->var_index++;
	}
	return (0);
}