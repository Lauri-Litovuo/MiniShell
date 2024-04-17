/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:08:21 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:14:53 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	DESCRIPTION
		char *strnstr(const char *big,	const char *little, size_t len);
       	The strnstr() function locates the first	occurrence of the  null-
		terminated  string little in the string big, where not more than len
		characters are	searched.  Characters that appear after	a `\0'	
		character  are not  searched.  Since the strnstr() function is a 
		FreeBSD specific API, it should only be used when portability is 
		not a concern.
	RETURN VALUES
       	If little is an empty string, big is returned; if little occurs 
		nowhere in big, NULL is returned; otherwise a pointer to the first 
		character of the first occurrence of little is returned.	*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0' && i + j <= len)
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
