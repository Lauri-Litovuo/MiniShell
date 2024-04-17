/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:37:56 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 14:36:33 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putnbr(int num, int *check)
{
	int	count;

	count = 0;
	if (num == -2147483648)
		return (count += ft_putstr("-2147483648", check));
	if (num < 0)
	{
		count += ft_putchar('-', check);
		num *= -1;
	}
	while (num > 9)
	{
		count += ft_putnbr((num / 10), check);
		num = num % 10;
	}
	if (num >= 0 && num <= 9)
		count += ft_putchar((num + 48), check);
	return (count);
}
