/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:21:33 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/19 17:21:51 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
