/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:44:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/11 15:21:29 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	init_expd_struct(t_expd *s);
int			expand_string(t_shell *arg, t_expd *s, t_vec *vec, int index);
int			check_if_exists(t_shell *arg, t_expd *s);
static void	check_extra_expand(t_expd *s, char *str);

int	expand_variables(t_shell *arg, t_vec *vec, int index)
{
	t_expd	s;

	init_expd_struct(&s);
	s.str = *(char **)vec_get(vec, index);
	s.total_len = ft_strlen(s.str);
	while (s.str[s.ds + 1] != '\0')
	{
		s.str = *(char **)vec_get(vec, index);
		s.total_len = ft_strlen(s.str);
		if (s.str[s.ds] == '$')
		{
			s.pre_len = s.ds;
			if (s.str[s.ds] == '$' && s.str[s.ds + 1] == '?')
				s.ret = expand_to_exit_status(arg, &s, vec, index);
			else
				s.ret = expand_string(arg, &s, vec, index);
		}
		if (s.ret < 0)
			return (-1);
		s.ds++;
	}
	return (0);
}

static void	init_expd_struct(t_expd *s)
{
	s->temp = NULL;
	s->str = NULL;
	s->expanded = NULL;
	s->env_var = NULL;
	s->new = NULL;
	s->var_len = 0;
	s->exp_len = 0;
	s->i = 0;
	s->ret = 0;
	s->index = 0;
	s->ds = 0;
}

int	expand_string(t_shell *arg, t_expd *s, t_vec *vec, int index)
{
	if (s->str[s->ds] == '\0' || s->str[s->ds + 1] == '$' 
		|| s->str[s->ds + 1] == ' ')
		return (0);
	s->ret = check_if_exists(arg, s);
	free(s->env_var);
	if (s->ret >= 0)
	{
		if (s->ret > 0)
		{
			if (expand_to_env_var(arg, s, vec, index) < 0)
				return (-1);
		}
		if (s->ret == 0)
		{
			if (expand_to_empty(s, vec, index) < 0)
				return (-1);
		}
		return (0);
	}
	else if (s->ret < 0)
		return (-1);
	return (0);
}

static void	check_extra_expand(t_expd *s, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			s->flag = 1;
		i++;
	}
}

int	check_if_exists(t_shell *arg, t_expd *s)
{
	s->i = s->ds + 1;
	while (s->str[s->i] && s->str[s->i] != '\'' && \
	s->str[s->i] != '$' && s->str[s->i] != ' ' && \
	(ft_isalnum(s->str[s->i]) != 0 || s->str[s->i] == '_' ))
		s->i++;
	check_extra_expand(s, &s->str[s->i]);
	s->var_len = s->i - s->ds - 1;
	s->env_var = ft_substr(s->str, s->ds + 1, s->var_len);
	if (!s->env_var)
		return (-1);
	s->var_index = 0;
	while (s->var_index < arg->env.len)
	{
		s->temp = extract_env_var(*(char **)vec_get(&arg->env, s->var_index));
		if (s->temp == NULL)
			return (-1);
		if (ft_strncmp(s->env_var, s->temp, s->var_len + 1) == 0)
		{
			free(s->temp);
			return (1);
		}
		s->var_index++;
		free(s->temp);
	}
	return (0);
}
