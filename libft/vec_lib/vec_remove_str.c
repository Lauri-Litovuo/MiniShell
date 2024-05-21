/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_remove_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:51:43 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/20 17:23:47 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
/********************************************************************
*	Removes and frees an element from index position in the vector 	*
*   without overwriting existing elements. 			                *
*	Returns: 1 on success, -1 on failure.							*
*********************************************************************/
#include <stdio.h>

int	vec_remove_str(t_vec *src, size_t index)
{
	char	*str;

	if (!src || index > src->len || !src->memory)
		return (-1);
	str = *(char **)vec_get(src, index);
	ft_memmove(vec_get(src, index), &src->memory[(index + 1) * src->elem_size], \
	(src->len - index) * src->elem_size);
	src->len--;
	free(str);
	return (1);
}
