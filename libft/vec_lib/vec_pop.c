/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:27:35 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 10:52:08 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "../includes/libft.h"

int	vec_pop(void *dst, t_vec *src)
{
	unsigned char	*elem_ptr;

	if (!src || !dst)
		return (-1);
	if (src->len == 0 || src->memory == NULL)
		return (0);
	elem_ptr = &src->memory[src->elem_size * (src->len - 1)];
	ft_memcpy(dst, elem_ptr, src->elem_size);
	src->len--;
	return (1);
}

int	main(void)
{
    t_vec   t1;
    int     base[] = {1, 2, 3, 4, 5};
    int     expect = 0;

    assert(vec_new(&t1, 1, sizeof(int)) > 0);
    vec_push(&t1, &base[1]);
    vec_push(&t1, &base[3]);
    vec_pop(&expect, &t1);
    assert(expect == 4);
    vec_pop(&expect, &t1);
    assert(expect == 2);
    assert(t1.len == 0);
    vec_free(&t1);
    printf("test_vec_pop successful!\n");
}
