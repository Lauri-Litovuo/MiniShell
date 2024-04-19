/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_from.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:19:09 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 11:34:30 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)	//DELETE WHEN COMBINED IN LIBFT
{
	size_t	i;
	char	*d;
	char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = (char *)dst;
	s = (char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

/********************************************************************
*	Description: Takes in a pointer to some memory, which then will	*
*	be copied over to the new vector.								*
*********************************************************************/
int vec_from(t_vec *dst, void *src, size_t len, size_t elem_size)
{
	if (!dst || !src || elem_size == 0)
		return (-1);
	if (vec_new(dst, len, elem_size) < 0)
		return (-1);
	ft_memcpy(dst->memory, src, dst->alloc_size);
	dst->len = len;
	return (1); 
}

// int main(void)
// {
//     t_vec   t1;
//     int     base[] = {1, 2, 3, 4, 5};

//     assert(vec_from(&t1, base, 5, sizeof(int)) > 0);
//     assert(memcmp(t1.memory, base, sizeof(base)) == 0);
//     vec_free(&t1);
//     printf("test_vec_from successful!\n");
// }
