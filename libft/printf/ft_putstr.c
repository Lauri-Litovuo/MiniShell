/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:37:45 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 14:36:24 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr(char *str, int *check)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str)
		return (ft_putstr("(null)", check));
	while (str[i])
	{
		count += ft_putchar(str[i], check);
		i++;
	}
	return (count);
}
