/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:04:41 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:04:50 by aneitenb         ###   ########.fr       */
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

	strlcat() 
	appends string src to the end of dst.  It will append at most
    dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
    dstsize is 0 or the original dst string was longer than dstsize (in prac-
    tice this should not happen as it means that either dstsize is incorrect
    or that dst is not a proper string).
	RETURN VALUE
	The following functions return the length of the total string
    that they tried to create (as if truncation didn't occur).*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;
	size_t	buffer;
	size_t	append;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	buffer = dlen;
	append = dstsize - dlen - 1;
	if (dstsize <= dlen)
		return (dstsize + slen);
	while (i < append && src[i] != '\0')
	{
		dst[buffer] = src[i];
		buffer++;
		i++;
	}
	dst[buffer] = '\0';
	return (dlen + slen);
}
