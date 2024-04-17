/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:46:49 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:01:24 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name ft_strjoin
	Parameters s1: The prefix string.
	s2: The suffix string.
	Return value: The new string.
	NULL if the allocation fails.
	External functs. malloc
	Description: Allocates (with malloc(3)) and returns a new
	string, which is the result of the concatenation
	of ’s1’ and ’s2’.	*/
char	*ft_strsjoin(char const *s1, char const *s2, char sep)
{
	char	*new;
	size_t	newlen;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	newlen = ft_strlen(s1) + ft_strlen(s2) + 2;
	new = malloc(newlen);
	if (new == NULL)
		return (NULL);
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	if (sep)
		new[j++] = sep;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	return (new);
}
