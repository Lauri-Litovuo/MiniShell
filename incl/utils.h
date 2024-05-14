/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:28:32 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/13 14:25:08 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_expd
{
	char	*temp;
	char	*str;
	char	*expanded;
	char	*env_var;
	char	*new;
	int		ret;
	size_t	var_len;
	size_t	exp_len;
	size_t	pre_len;
	size_t	total_len;
	size_t	index;
	size_t	ds;
	size_t	i;
	size_t	var_index;
}	t_expd;

extern int	g_exit_status;

//int		expand_variables(t_vec *env, t_shell *arg);
int		expand_cmd_and_rdrct(t_vec *env, t_vec *vec);
int		expand_string(t_vec *env, t_expd *s, t_vec *vec);
int		expand_to_env_var(t_vec *env, t_expd *s, t_vec *vec);
int		expand_to_exit_status(t_expd *s, t_vec *vec);
int		expand_to_empty(t_expd *s, t_vec *vec);
void	free_expd(t_expd *s);

#endif

