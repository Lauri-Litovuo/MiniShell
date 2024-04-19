/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:21:33 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 15:33:22 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/****************************************************************************
*	Takes as an argument a function f applied to each element in the vector	*
*****************************************************************************/

void	vec_iter(t_vec *src, void (*f) (void *))
{
	size_t	i;

	i = 0;
	while (i < src->len)
	{
		(*f)(&src->memory[i * src->elem_size]);
		i++;
	}
}

// void iter_tester(void *src)
// {
//     *(int *)src += 1;
// }

// int main(void)
// {
//     t_vec   t1;
//     int     base[] = {1, 2, 3, 4, 5};
//     int     expect[] = {2, 3, 4, 5, 6};

//     assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
//     vec_iter(&t1, iter_tester);
//     assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
//     vec_free(&t1);
//     printf("test_vec_iter successful!\n");
// }