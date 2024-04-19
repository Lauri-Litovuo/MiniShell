/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:41:42 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 14:50:58 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief appends source to the end of the destination vector
 * 
 * @param dst destination vector
 * @param src source vector
 * @return int Returns 1 if success, -1 if not.
 */

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
/*
int main(void)
{
    t_vec   t1;
    t_vec   t2;
    int     base1[] = {1, 2, 3};
    int     base2[] = {4, 5, 6};
    int     expect[] = {1, 2, 3, 4, 5, 6};
	size_t i;

	i = 0;
    assert(vec_from(&t1, base1, 3, sizeof(int)) > 0);
    assert(vec_from(&t2, base2, 3, sizeof(int)) > 0);
    assert(vec_append(&t1, &t2) > 0);
	while (i < t1.len)
	{
		printf("dst[%zu]: %d\n", i, t1.memory[i * sizeof(int)]);
		i++;
	}
    assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
    vec_free(&t1);
    vec_free(&t2);
    printf("test_vec_append successful!\n");
}*/