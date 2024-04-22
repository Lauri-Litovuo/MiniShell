/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:13:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/22 12:19:22 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/********************************************************************
*	Creates a new vector which memory size is init_len*elem_size. 	*
*	Does not allocate memory for the t_vec.							*
*	Returns: 1 on success, -1 on failure.							*
*********************************************************************/

int	vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
	if (!dst || elem_size == 0)
		return (-1);
	dst->alloc_size = init_len * elem_size;
	dst->len = 0;
	dst->elem_size = elem_size;
	if (init_len == 0)
		dst->memory = NULL;
	else
	{
		dst->memory = ft_calloc(elem_size, init_len);
		if (!dst->memory)
			return (-1);
	}
	return (1);
}
