/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:28:32 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/31 15:19:13 by aneitenb         ###   ########.fr       */
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
	int		flag;
	size_t	var_len;
	size_t	exp_len;
	size_t	pre_len;
	size_t	total_len;
	size_t	index;
	size_t	ds;
	size_t	i;
	size_t	var_index;
}	t_expd;

int		expand_variables(t_vec *env, t_vec *vec, int index);
char	*extract_env_var(char *arg);
int		check_if_exists(t_vec *env, t_expd *s);
int		expand_string(t_vec *env, t_expd *s, t_vec *vec, int index);
int		expand_to_env_var(t_vec *env, t_expd *s, t_vec *vec, int index);
int		expand_to_exit_status(t_expd *s, t_vec *vec);
int		expand_to_empty(t_expd *s, t_vec *vec, int index);
void	free_expd(t_expd *s);


#endif
