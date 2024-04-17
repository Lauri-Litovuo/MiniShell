/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:02:25 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:09:40 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name: ft_substr
	Parameters s: The string from which to create the substring.
	start: The start index of the substring in the
	string ’s’.
	len: The maximum length of the substring.
	Return value: The substring.
	NULL if the allocation fails.
	External functs. malloc
	Description: Allocates (with malloc(3)) and returns a substring
	from the string ’s’.
	The substring begins at index ’start’ and is of
	maximum size ’len’.	*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*substring;

	if (!s)
		return (NULL);
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		len = 0;
	i = 0;
	j = 0;
	substring = malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			substring[j++] = s[i];
		i++;
	}
	substring[j] = '\0';
	return (substring);
}
