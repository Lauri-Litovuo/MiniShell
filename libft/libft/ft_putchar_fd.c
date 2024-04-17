/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:06:32 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:57:35 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name: ft_putchar_fd
	Parameters c: The character to output.
	fd: The file descriptor on which to write.
	Return value: None
	External functs. write
	Description: Outputs the character ’c’ to the given file
	descriptor.	*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
