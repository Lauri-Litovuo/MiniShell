/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:52:55 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:02:00 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name: ft_strtrim
	Prototype char *ft_strtrim(char const *s1, char const *set);
	Parameters s1: The string to be trimmed.
	set: The reference set of characters to trim.
	Return value: The trimmed string.
	NULL if the allocation fails.
	External functs. malloc
	Description: Allocates (with malloc(3)) and returns a copy of
	’s1’ with the characters specified in ’set’ removed
	from the beginning and the end of the string.*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > 0 && ft_strchr(set, s1[j - 1]))
		j--;
	if (j <= i)
		return (ft_calloc(sizeof(char), 1));
	trimmed = malloc((j - i + 1) * (sizeof(char)));
	if (trimmed == NULL)
		return (NULL);
	ft_strlcpy(trimmed, &s1[i], (j - i + 1));
	return (trimmed);
}
