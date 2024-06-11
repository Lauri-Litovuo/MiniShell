/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_replace_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:30:47 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/11 17:44:05 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

int	vec_replace_str(t_vec *dst, void *src, size_t index)
{
	if (!dst || !src || index > dst->len)
		return (-1);
	if (vec_remove(dst, (size_t)index) < 0)
		return (-1);
	if (vec_insert(dst, &src, index) < 0)
		return (-1);
	return (1);
}
