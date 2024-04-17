/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:42:32 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:01:33 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putun(unsigned int num, int *check)
{
	int	count;

	count = 0;
	while (num > 9)
	{
		count += ft_putnbr((num / 10), check);
		num = num % 10;
	}
	if (num >= 0 && num <= 9)
		count += ft_putchar((num + 48), check);
	return (count);
}
