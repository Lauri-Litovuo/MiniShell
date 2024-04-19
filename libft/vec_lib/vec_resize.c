/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:43:01 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 17:37:15 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/************************************************************
*	Takes in a target_size parameter and either shrinks		*
*	(destructively) or grows the vector to the target size,	* 
*	copying the old contents over to the new allocation.	*
*	Returns: 1 upon success, and -1 on error.				*
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
