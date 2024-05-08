/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:44:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/08 14:37:42 by llitovuo         ###   ########.fr       */
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
		s.str = *(char **)vec_get(vec, s.i);
		while (*s.str != '\0')
		{
			if (s.str == '$' && *(s.str + 1) != '$')
			{
				check_if_exists(env, &s);
				if (s.ret > 0)
				{
					if (expand_to_env_var(env, s.expanded, vec, s.ret) < 0)
						return (-1);
				}
				else if (s.ret < 0)
					return (-1);
			}
			else if (*s.str == '$' && *(s.str + 1) == '$')
			{
				if (get_pid(s.expanded) < 0)
					return (-1);
			}
			s.str++;
		}
		s.index++;
	}
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

int	check_if_exists(t_vec *env, t_expd *s)
{
	size_t	i;
	char	*str; //change name
	char	*env_var;

	i = 1;
	while (s->str[i] != '\0' && (ft_isalnum(s->str[i]) != 0 || s->str[i] == '_'))
		i++;
	str = ft_substr(s->str, 1, i);
	if (!str)
		return (-1);
	i = 0;
	while (i < env->len)
	{
		env_var = extract_env_var(*(char **)vec_get(env, i));
		if (env_var == NULL)
			return (free (str), -1);
		if (ft_strncmp(env_var, str, ft_strlen(str)) == 0
			&& *(env_var + ft_strlen(str) + 1) == '=')
		{
			i = ft_strlen(str);
			free(str);
			free(env_var);
			return (i);
		}
		free (env_var);
		i++;
	}
	return (0);
}


int	expand_to_env_var(t_vec *env, char *expand, t_vec *vec, int len)
{
	char	*temp;
	int		full_len;

	//calculate needed space for prepart+expanded_variable+rest;
	//malloc enough space
	//take substring prepart
	//strcat expanded_variable, rmbr to skip $
	//strcat rest;
	//replace to t_vec vec to right s.index;
	ft_substr(s->str, )
}

int	get_pid(char *expand)
{
	expand = ft_strdup("12312"); //arb value, make better
	return (0);
}
