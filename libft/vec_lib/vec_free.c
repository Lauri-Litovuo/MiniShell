/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:28:07 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/17 14:01:10 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
/**
 * @brief Frees memory and zeroes vector fields.
 * 
 * @param src 
 */

void	vec_free(t_vec *src)
{
	free(src->memory);
	src->memory = NULL;
	src->len = 0;
	src->elem_size = 0;
	src->alloc_size = 0;
}

/*int main(void)
{
    t_vec t1;

    assert(vec_new(&t1, 10, 1) > 0);
    vec_free(&t1);
    assert(t1.len == 0);
    assert(t1.alloc_size == 0);
    assert(t1.elem_size == 0);
    assert(t1.memory == NULL);
    printf("test_vec_free successful!\n");
}*/