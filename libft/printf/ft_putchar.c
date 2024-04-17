/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:48:16 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 14:36:46 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putchar(char c, int *check)
{
	if (*check == -1)
		return (-1);
	if (write(1, &c, 1) == -1)
	{
		*check = -1;
		return (-1);
	}
	return (1);
}
