/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:04:32 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 14:31:59 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*save_remainder(char *buffer)
{
	int		i;
	int		j;
	char	*string;

	j = 0;
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	i++;
	string = buffer;
	while (buffer[i] != '\0')
	{
		string[j] = buffer[i];
		i++;
		j++;
	}
	string[j] = '\0';
	return (string);
}

char	*get_lines(char *buffer)
{
	int		i;
	char	*string;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	string = ft_calloc(sizeof(char), i + 1);
	if (string == NULL)
	{
		free(buffer);
		return (NULL);
	}
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		string[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		string[i++] = '\n';
	return (string);
}

char	*read_bit(char *string, char *buffer, int fd)
{
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		string = ft_strjoin_gnl(string, buffer);
		if (string == NULL)
			return (NULL);
		if (ft_strchr(string, '\n') != 0)
			break ;
	}
	return (string);
}

char	*read_line(int fd, char *buffer)
{
	char	*string;

	string = ft_calloc(sizeof(char), 1);
	if (string == NULL )
		return (ft_free_gnl(buffer));
	if (!buffer)
		buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (ft_free_gnl(string));
	string = ft_strjoin_gnl(string, buffer);
	if (string == NULL)
		return (ft_free_gnl(buffer));
	string = read_bit(string, buffer, fd);
	if (string == NULL)
		return (ft_free_gnl(buffer));
	ft_free_gnl(buffer);
	return (string);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*string;

	if (read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_line(fd, buffer);
	if (buffer == NULL || buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	string = get_lines(buffer);
	if (string == NULL)
	{
		buffer = NULL;
		return (NULL);
	}
	buffer = save_remainder(buffer);
	return (string);
}
