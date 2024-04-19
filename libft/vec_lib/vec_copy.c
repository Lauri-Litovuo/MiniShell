/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:53:49 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 12:47:10 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/************************************************************************
*	The copy function is very simple and will only copy at most			*
*	as many bytes as are available in the dst vector-- not true?		*
*************************************************************************/
int	vec_copy(t_vec *dst, t_vec *src)
{
	size_t	copy_size;

	if (!dst || !src || !src->memory)
		return (-1);
	else if (!dst->memory)
		vec_new(dst, src->len, dst->elem_size);
	if (src->len * src->elem_size < dst->alloc_size)
		copy_size = src->len * src->elem_size;
	else
		copy_size = src->alloc_size;
	ft_memcpy(dst->memory, src->memory, copy_size);
	dst->len = copy_size / dst->elem_size;
	return (1);
}
//	how come the function copies more than is available in the dst? 
//	dst memory literally gets overwritten by how much is in the src vector. 
/*int main(void)
{
    t_vec   t1;
    t_vec   t2;
    int     base[] = {1, 2, 3, 4, 5};
	char 

    assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
    assert(vec_new(&t2, 3, sizeof(int)) > 0);
    assert(vec_copy(&t2, &t1) > 0);
    assert(memcmp(t2.memory, base, sizeof(base)) == 0);
	printf("dst[1]: %d\n", t2.memory[1 * sizeof(int)]);
	printf("dst[2]: %d\n", t2.memory[2 * sizeof(int)]);
	printf("dst[3]: %d\n", t2.memory[3 * sizeof(int)]);
	printf("dst[4]: %d\n", t2.memory[4 * sizeof(int)]);
	printf("dst[5]: %d\n", t2.memory[5 * sizeof(int)]);
	printf("dst[6]: %d\n", t2.memory[6 * sizeof(int)]);
    vec_free(&t1);
    vec_free(&t2);
    printf("test_vec_copy successful!\n");
}*/
