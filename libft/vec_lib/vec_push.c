/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:55:25 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/24 14:32:41 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/********************************************************************
*	Takes in a vector and a pointer to an element to be pushed to	*
*	the end of the vector.											*
*	Returns: 1 on success, -1 on failure.							*
*********************************************************************/

int	vec_push(t_vec *dst, void *src)
{
	if (!src || !dst)
		return (-1);
	else if (!dst->memory)
		vec_new(dst, 1, dst->elem_size);
	if (dst->len * dst->elem_size >= dst->alloc_size)
	{
		if (vec_resize(dst, dst->len * 2) == -1)
			return (-1);
	}
	ft_memcpy(&dst->memory[dst->elem_size * dst->len], src, dst->elem_size);
	dst->len++;
	return (1);
}
