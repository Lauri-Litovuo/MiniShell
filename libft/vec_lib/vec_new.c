/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:13:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 14:03:36 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
/**
 * @brief Creates a new vector which memory size is init_len*elem_size. 
 * Does not allocate memory for the t_vec
 * 
 * @param dst pointer to t_vec pointer
 * @param init_len initialization used lenght.
 * @param elem_size size of vector element in bytes
 * @return int returns 1 on success and -1 on malloc or param fail
 */

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
		dst->memory = (unsigned char *) malloc(init_len * elem_size);
		if (!dst->memory)
			return (-1);
	}
	return (1);
}

/*int	main(void)
{
    t_vec t1;

    assert(vec_new(&t1, 0, 0) == -1);
    assert(vec_new(&t1, 0, 1) > 0);
    assert(t1.memory == NULL);
    assert(vec_new(&t1, 1, 0) == -1);
    assert(vec_new(&t1, 10, 1) > 0);
    assert(t1.memory != NULL);
    vec_free(&t1);
    printf("test_vec_new successful!\n");
}*/