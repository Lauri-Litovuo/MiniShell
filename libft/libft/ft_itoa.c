/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:28:05 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:47:56 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name: ft_itoa
	Parameters n: the integer to convert.
	Return value: The string representing the integer.
	NULL if the allocation fails.
	External functs. malloc
	Description Allocates (with malloc(3)) and returns a string
	representing the integer received as an argument.
	Negative numbers must be handled.	*/
static char	*ft_make(char *str, int len, int n)
{
	int	i;

	i = len - 1;
	if (n == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 9)
	{
		str[i--] = (n % 10) + 48;
		n = n / 10;
	}
	str[i--] = (n + 48);
	return (str);
}

static int	ft_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_make(str, len, n);
	str[len] = '\0';
	return (str);
}
