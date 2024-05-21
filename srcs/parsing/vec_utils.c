/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:37:58 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/21 13:57:31 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	vec_replace_special(t_vec *dst, void *src, size_t index)
{
	char	*str;

	if (!dst || !src || index > dst->len)
		return (-1);
	str = *(char **)vec_get(dst, index);
	if (vec_insert(dst, &src, index) < 0)
		return (-1);
	if (vec_remove(dst, (size_t)index + 1) < 0)
		return (-1);
	free(str);
	return (1);
}
