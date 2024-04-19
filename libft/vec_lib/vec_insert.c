/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:34:36 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 14:13:45 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/********************************************************************
*	Inserts a new element at any position in the vector without		*
*	overwriting existing elements.									*
*	Returns: 1 on success, -1 on failure.							*
*********************************************************************/

int	vec_insert(t_vec *dst, void *src, size_t index)
{
	if (!dst || !src || index > dst->len)
		return (-1);
	else if (index == dst->len)
		return (vec_push(dst, src));
	if (dst->elem_size * dst->len >= dst->alloc_size)
		if (vec_resize(dst, (dst->alloc_size * 2) / dst->elem_size) < 0)
			return (-1);
	ft_memmove(vec_get(dst, index + 1), vec_get(dst, index),
		(dst->len - index) * dst->elem_size);
	ft_memcpy(vec_get(dst, index), src, dst->elem_size);
	dst->len++;
	return (1);
}

// int main(void)
// {
//     t_vec   t1;
//     int     base[] = {1, 2, 3, 4, 5};
//     int     insert[] = {42, 666, 7};
//     int     expect[] = {1, 42, 2, 3, 666, 4, 5, 7};

//     assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
//     vec_insert(&t1, &insert[0], 1);
//     vec_insert(&t1, &insert[1], 4);
//     vec_insert(&t1, &insert[2], 7);
//     assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
//     vec_free(&t1);
//     printf("test_vec_insert successful!\n");
// }