/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:57:28 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 14:36:13 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putptr(void *ptr, int *check)
{
	int	count;

	count = 0;
	count += ft_putstr("0x", check);
	count += ft_puthexbase((unsigned long)ptr, 0, check);
	return (count);
}
