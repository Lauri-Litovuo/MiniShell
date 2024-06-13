/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:03:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/13 14:45:14 by aneitenb         ###   ########.fr       */
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
	vec_free(src);
}
