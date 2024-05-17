/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:45:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/17 10:14:52 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	init_exe(t_exec *exe, size_t count);
static void	init_env_ex(t_env *ex_env, size_t count);

// static void	print_vec(t_vec *vec) //del
// {
// 		for(size_t i = 0; i < vec->len; i++)
// 			printf("ex_env: %s\n", *(char **)vec_get(vec, i));
// }


