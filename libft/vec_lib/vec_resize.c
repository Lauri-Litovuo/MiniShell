/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:43:01 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 12:22:40 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/************************************************************
*	Takes in a target_size parameter and either shrinks		*
*	(destructively) or grows the vector to the target size,	* 
*	copying the old contents over to the new allocation.	*
*	RETURNS: 1 upon success, and -1 on error.				*
*************************************************************/
static int vec_resize(t_vec *src, size_t target_size)
{
	if (!src)
		return (-1);
	else if (!src->memory)
		return (vec_new(src, target_size, src->elem_size));
	ft_memcpy(src, src, target_size);
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