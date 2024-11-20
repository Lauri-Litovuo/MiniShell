/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:48:18 by aneitenb          #+#    #+#             */
/*   Updated: 2024/11/20 14:01:26 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name: ft_putnbr_fd
	Parameters n: The integer to output.
	fd: The file descriptor on which to write.
	Return value: None
	External functs. write
	Description: Outputs the integer ’n’ to the given file
	descriptor.	*/
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	new;

	if (n < 0)
	{
		new = (unsigned int)(n * -1);
		ft_putchar_fd('-', fd);
	}
	else
		new = (unsigned int)n;
	if (new > 9)
	{
		ft_putnbr_fd(new / 10, fd);
		new = new % 10;
	}
	if (new <= 9)
		ft_putchar_fd((new + 48), fd);
}
