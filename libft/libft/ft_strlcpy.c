/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:01:49 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:05:25 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*  DESCRIPTION
	strlcpy(3bsd)
    strlcat(3bsd)
    	These functions copy and catenate the input string into a
        destination string.  If the destination buffer, limited by
        its size, isn't large enough to hold the copy, the
        resulting string is truncated (but it is guaranteed to be
        null-terminated).  They return the length of the total
        string they tried to create.  These functions force a
        SIGSEGV if the src pointer is not a string.
	RETURN VALUE
		The following functions return the length of the total string
       	that they tried to create (as if truncation didn't occur).*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < (dstsize - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
