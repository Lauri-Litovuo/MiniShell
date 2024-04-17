/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:50:13 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:56:38 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	DESCRIPTION         
       The memset() function fills the first n bytes of the memory area
       pointed to by s with the constant byte c.
	RETURN VALUE
       The memset() function returns a pointer to the memory area s.*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)b;
	while (i < len)
	{
		str[i] = ((unsigned char)c);
		i++;
	}
	return (b);
}
