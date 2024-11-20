/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:42:32 by aneitenb          #+#    #+#             */
/*   Updated: 2024/11/20 14:04:35 by llitovuo         ###   ########.fr       */
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
	if (num <= 9)
		count += ft_putchar((num + 48), check);
	return (count);
}
