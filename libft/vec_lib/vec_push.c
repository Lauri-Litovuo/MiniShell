/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:55:25 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 12:45:53 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief Function takes in a vector and a pointer to an element
 *  to be pushed to the end of the vector
 * 
 * @param dst t_vec destination
 * @param src void *source added end of the destination vector
 * @return int returns -1 if failed, returns 1 if successful. 
 */

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
	if (ft_memcpy(&dst->memory[dst->elem_size * dst->len], src, dst->elem_size) \
	== NULL)
		return (-1);
	dst->len++;
	return (1);
}

/*int main(void)
{
    t_vec   t1;
    int     base[] = {1, 2, 3, 4, 5};
    int     expect[] = {2, 4};

    assert(vec_new(&t1, 1, sizeof(int)) > 0);
    vec_push(&t1, &base[1]);
    vec_push(&t1, &base[3]);
	printf("t1.mem: %d\n", (int)t1.memory[0]);
    assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
    vec_free(&t1);
    printf("test_vec_push successful!\n");
}*/