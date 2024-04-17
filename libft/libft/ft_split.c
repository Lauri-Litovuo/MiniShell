/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:50:21 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:59:26 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	word_len(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static void	ft_free(char **array, int index)
{
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	free(array);
}

static int	count_strings(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	return (count);
}

static	char	**make_array(char *str, char c, int count, char **array)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < count)
	{
		while (str[j] == c)
			j++;
		array[i] = ft_substr(&str[j], 0, (word_len(&str[j], c)));
		if (array[i] == NULL)
		{
			ft_free(array, i);
			return (NULL);
		}
		j += ft_strlen(array[i]);
		i++;
	}
	array[i] = NULL;
	return (array);
}

/*	Function name: ft_split
	Parameters s: The string to be split.
	c: The delimiter character.
	Return value: The array of new strings resulting from the split.
	NULL if the allocation fails.
	External functs. malloc, free
	Description: Allocates (with malloc(3)) and returns an array
	of strings obtained by splitting ’s’ using the
	character ’c’ as a delimiter. The array must end
	with a NULL pointer.*/
char	**ft_split(char const *s, char c)
{
	int		count;
	char	*str;
	char	**array;

	if (!s)
		return (NULL);
	str = (char *)s;
	count = count_strings(str, c);
	array = malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = make_array(str, c, count, array);
	return (array);
}
