/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:34:36 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/14 20:04:49 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/********************************************************************
*	Inserts a new element at any position in the vector without		*
*	overwriting existing elements.									*
*	Returns: 1 on success, -1 on failure.							*
*********************************************************************/

int	vec_insert(t_vec *dst, void *src, size_t index)
{
	if (!src || !src || index > dst->len)
		return (-1);
	else if (index == dst->len)
	{
		return (vec_push(dst, src));
	}
	if (dst->alloc_size <= (dst->len) * dst->elem_size)
	{
		if (vec_resize(dst, 2 * dst->alloc_size) <= 0)
			return (-1);
	}
	ft_memmove(&dst->memory[(index + 1) * dst->elem_size],
		&dst->memory[index * dst->elem_size],
		(dst->len - index) * dst->elem_size);
	ft_memcpy(vec_get(dst, index), src, dst->elem_size);
	dst->len++;
	return (dst->len);
}
