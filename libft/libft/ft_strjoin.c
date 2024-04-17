/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:00:44 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:13:21 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name: ft_strjoin
	Parameters s1: The prefix string.
	s2: The suffix string.
	Return value: The new string.
	NULL if the allocation fails.
	External functs. malloc
	Description: Allocates (with malloc(3)) and returns a new
	string, which is the result of the concatenation
	of ’s1’ and ’s2’.*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	newlen;

	if (!s1 || !s2)
		return (NULL);
	newlen = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = malloc(newlen);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, s1, newlen);
	ft_strlcat(new, s2, newlen);
	return (new);
}
