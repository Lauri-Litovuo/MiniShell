/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:03:02 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 17:31:28 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/************************************************
*	Returns a pointer to the element at index	*
*************************************************/

void	*vec_get(t_vec *src, size_t index)
{
	unsigned char	*elem_ptr;

	if (!src || index >= src->len || !src->memory)
		return (NULL);
	elem_ptr = &src->memory[src->elem_size * index];
	return (elem_ptr);
}
