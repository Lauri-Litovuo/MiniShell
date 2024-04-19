/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_prepend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:20:02 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 17:35:03 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/********************************************
*	Prepends vector src to dst.				*
*	Returns: 1 on success, -1 on failure.	*
*********************************************/

int	vec_prepend(t_vec *dst, t_vec *src)
{
	t_vec	joined;
	size_t	alloc_size;

	if (!dst || !src)
		return (-1);
	if (!dst->memory)
		vec_new(dst, 1, dst->elem_size);
	alloc_size = (dst->len * dst->elem_size) + (src->len * src->elem_size);
	vec_new(&joined, alloc_size / dst->elem_size, dst->elem_size);
	vec_copy(&joined, src);
	joined.len = src->len + dst->len;
	ft_memcpy(&joined.memory[(src->len * src->elem_size)], dst->memory,
		dst->elem_size * dst->len);
	vec_free(dst);
	*dst = joined;
	return (1);
}
