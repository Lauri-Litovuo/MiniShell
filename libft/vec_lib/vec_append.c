/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:41:42 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 17:28:26 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/********************************************************
 *	Appends source to the end of the destination vector	*
 *	Returns: (int) 1 if success, -1 if not.				*
 ********************************************************/

int	vec_append(t_vec *dst, t_vec *src)
{
	if (!dst || !src || !src->memory)
		return (-1);
	if (!dst->memory)
		vec_new(dst, src->len, src->elem_size);
	if (dst->alloc_size < \
	(dst->len * dst->elem_size) + (src->len * src->elem_size))
	{
		if (vec_resize(dst, \
		(dst->len * dst->elem_size) + (src->len * src->elem_size)) == -1)
			return (-1);
	}
	if (ft_memcpy(&dst->memory[dst->elem_size * dst->len], \
	src->memory, src->len * src->elem_size) == NULL)
		return (-1);
	dst->len += src->len;
	return (1);
}
