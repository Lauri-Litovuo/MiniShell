/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 09:28:32 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/16 12:08:40 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		expand_variables(t_shell *arg, t_vec *vec, int index);
char	*extract_env_var(char *arg);
int		check_if_exists(t_shell *arg, t_expd *s);
int		expand_string(t_shell *arg, t_expd *s, t_vec *vec, int index);
int		expand_to_env_var(t_shell *arg, t_expd *s, t_vec *vec, int index);
int		expand_to_exit_status(t_shell *arg, t_expd *s, t_vec *vec, int index);
int		expand_to_empty(t_expd *s, t_vec *vec, int index);
void	get_count(t_vec *vec, int index, t_expd *s);

#endif