/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:01:41 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:52:26 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	DESCRIPTION
    isascii()
        checks whether c is a 7-bit unsigned char value that fits
        into the ASCII character set.
	RETURN VALUE
       The values returned are nonzero if the character c falls into the
       tested class, and zero if not.	*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
