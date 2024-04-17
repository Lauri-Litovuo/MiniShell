/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:08:48 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:07:17 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	DESCRIPTION
		The strncmp() function shall compare not more than n bytes (bytes
       	that follow a NUL character are not compared) from the array
       	pointed to by s1 to the array pointed to by s2.

       	The sign of a non-zero return value is determined by the sign of
       	the difference between the values of the first pair of bytes
       	(both interpreted as type unsigned char) that differ in the
       	strings being compared.
	RETURN VALUE
       	Upon successful completion, strncmp() shall return an integer
       	greater than, equal to, or less than 0, if the possibly null-
       	terminated array pointed to by s1 is greater than, equal to, or
       	less than the possibly null-terminated array pointed to by s2
       	respectively.*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				rtn;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((i < n - 1) && str1[i] == str2[i] && str1[i] != '\0')
	{
		i++;
	}
	rtn = str1[i] - str2[i];
	return (rtn);
}
