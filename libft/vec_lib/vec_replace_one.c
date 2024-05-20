/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_replace_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidaneitenbach <aidaneitenbach@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:36:49 by aidaneitenb       #+#    #+#             */
/*   Updated: 2024/05/19 22:31:48 by aidaneitenb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	vec_replace_one(t_vec *dst, void *src, size_t index)
{
	if (!dst || !src || index > dst->len)
		return (-1);
	if (vec_remove(dst, index) < 0)
		return (-1);
	if (vec_insert(dst, src, index) < 0)
		return (-1);
	return (1);
}
