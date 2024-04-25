/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:03:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/25 16:22:01 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/************************************************
 *  Frees strings and zeroes vector fields.    	*
 ************************************************/

void	vec_free_str(t_vec *src)
{
	char	*str_ptr;
	size_t	i;

	i = 0;
	while (i < src->len)
	{
		str_ptr = *(char **)vec_get(src, i);
		free(str_ptr);
		i++;
	}
	src->memory = NULL;
	src->len = 0;
	src->elem_size = 0;
	src->alloc_size = 0;
}
