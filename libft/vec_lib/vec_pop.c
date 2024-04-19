/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:27:35 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 17:39:48 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/********************************************************************
*	Removes the last element from the vector and copies it to dst. 	*
*	Returns: 1 on success, -1 on failure.							*
*********************************************************************/

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
