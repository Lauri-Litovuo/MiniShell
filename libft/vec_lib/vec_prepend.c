/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_prepend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:20:02 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 15:15:54 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/********************************************
*	Prepends vector src to dst				*
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

// int main(void)
// {
//     t_vec   t1;
//     t_vec   t2;
//     int     base1[] = {1, 2, 3};
//     int     base2[] = {4, 5, 6};
//     int     expect[] = {4, 5, 6, 1, 2, 3};
// 	// size_t	i = 0;

//     assert(vec_from(&t1, base1, 3, sizeof(int)) > 0);
//     assert(vec_from(&t2, base2, 3, sizeof(int)) > 0);
//     assert(vec_prepend(&t1, &t2) > 0);
// 	// while (i < t1.len)
// 	// {
// 	// 	printf("t1[%zu]: %d\n", i, t1.memory[i * sizeof(int)]);
// 	// 	i++;
// 	// }
//     assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
//     vec_free(&t1);
//     vec_free(&t2);
//     printf("test_vec_prepend successful!\n");
// }
