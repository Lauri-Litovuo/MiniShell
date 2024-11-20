/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:19:02 by aneitenb          #+#    #+#             */
/*   Updated: 2024/11/20 14:02:53 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	DESCRIPTION	
       The strrchr() function returns a pointer to the last occurrence
       of the character c in the string s.

       Here "character" means "byte"; these functions do not work with
       wide or multibyte characters.
	RETURN VALUE
       The strchr() and strrchr() functions return a pointer to the
       matched character or NULL if the character is not found.  The
       terminating null byte is considered part of the string, so that
       if c is specified as '\0', these functions return a pointer to
       the terminator.	*/
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen((char *)s);
	while (i)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		if (i == 0)
			break ;
		i--;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	else
		return (0);
}
