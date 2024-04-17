/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:53:48 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:10:04 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	DESCRIPTION
       These functions convert lowercase letters to uppercase, and vice
       versa.
	RETURN VALUE
       The value returned is that of the converted letter, or c if the
       conversion was not possible.	*/
int	ft_tolower(int c)
{
	if (c >= 97 && c <= 122)
		return (c);
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}
