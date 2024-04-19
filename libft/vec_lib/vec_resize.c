/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:43:01 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 12:45:30 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/************************************************************
*	Takes in a target_size parameter and either shrinks		*
*	(destructively) or grows the vector to the target size,	* 
*	copying the old contents over to the new allocation.	*
*	RETURNS: 1 upon success, and -1 on error.				*
*************************************************************/
int	vec_resize(t_vec *src, size_t target_size)
{
	t_vec	dst;

	if (!src)
		return (-1);
	else if (!src->memory)
		return (vec_new(src, target_size, src->elem_size));
	else if (vec_new(&dst, target_size, src->elem_size) < 0)
		return (-1);
	ft_memcpy(dst.memory, src->memory, src->len * src->elem_size);
	dst.len = src->len;
	vec_free(src);
	*src = dst;
	return (1);
}

// int main(void)
// {
//     t_vec   t1;
//     int     base[] = {1, 2, 3, 4, 5};

//     assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
//     assert(vec_resize(&t1, 100) > 0);
//     assert(memcmp(t1.memory, base, sizeof(base)) == 0);
//     vec_free(&t1);
//     printf("test_vec_resize successful!\n");
// }