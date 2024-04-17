/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:04:56 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 14:32:10 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin_gnl(char *string, char *buffer)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!string || !buffer)
		return (NULL);
	new = malloc(ft_strlen(string) + ft_strlen(buffer) + 1);
	if (new == NULL)
		return (ft_free_gnl(string));
	while (string[i] != '\0')
	{
		new[i] = string[i];
		i++;
	}
	while (buffer[j] != '\0')
	{
		new[i] = buffer[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(string);
	return (new);
}

char	*ft_free_gnl(char *string)
{
	free(string);
	string = NULL;
	return (NULL);
}
