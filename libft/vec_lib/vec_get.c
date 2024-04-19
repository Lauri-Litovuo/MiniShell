/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:03:02 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 12:46:52 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	*vec_get(t_vec *src, size_t index)
{
	unsigned char	*elem_ptr;

	if (!src || index >= src->len || !src->memory)
		return (NULL);
	elem_ptr = &src->memory[src->elem_size * index];
	return (elem_ptr);
}

/*int main(void)
{
    t_vec   t1;
    int     base[] = {1, 2, 3, 4, 5};
    int     *expect;

    assert(vec_new(&t1, 1, sizeof(int)) > 0);
    vec_push(&t1, &base[1]);
    vec_push(&t1, &base[3]);
    expect = vec_get(&t1, 0);
    assert(*expect == 2);
    expect = vec_get(&t1, 1);
    assert(*expect == 4);
    assert(t1.len == 2);
    vec_free(&t1);
    printf("test_vec_get successful!\n");
}*/
