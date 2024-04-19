/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:21:39 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 13:42:21 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/**
 * @brief Removes an element from index position 
 * in the vector without overwriting existing elements
 * 
 * @param src The source vector
 * @param index index number of the removable element
 * @return int Returns 1 if successful, -1 if not.
 */

int	vec_remove(t_vec *src, size_t index)
{
	if (!src || index > src->len || !src->memory)
		return (-1);
	ft_memmove(vec_get(src, index), &src->memory[(index + 1) * src->elem_size], \
	(src->len - index) * src->elem_size);
	src->len--;
	return (1);
}

/*int main(void)
{
    t_vec   t1;
    int     base[] = {1, 2, 3, 4, 5};
    int     insert[] = {42, 666, 7};

    assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
    vec_insert(&t1, &insert[0], 1);
    vec_insert(&t1, &insert[1], 4);
    vec_insert(&t1, &insert[2], 7);
    vec_remove(&t1, 1);
    vec_remove(&t1, 3);
    vec_remove(&t1, 5);
    assert(memcmp(t1.memory, base, sizeof(base)) == 0);
    vec_free(&t1);
    printf("test_vec_remove successful!\n");
}*/
