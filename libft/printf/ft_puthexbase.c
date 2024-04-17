/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:13:54 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 14:36:40 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_puthexbase(unsigned long num, int cap, int *check)
{
	int	count;

	count = 0;
	if (num >= 16)
	{
		count += ft_puthexbase((num / 16), cap, check);
		count += ft_puthexbase((num % 16), cap, check);
	}
	if (cap == 0 && (num >= 10 && num <= 15))
		count += ft_putchar((num + 87), check);
	if (cap == 1 && (num >= 10 && num <= 15))
		count += ft_putchar((num + 55), check);
	if (num <= 9)
		count += ft_putnbr(num, check);
	return (count);
}
