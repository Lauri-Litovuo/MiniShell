/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:57:35 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:52:28 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	DESCRIPTION
    isalpha()
        checks for an alphanumeric character; it is equivalent to
        (isalpha(c) || isdigit(c)).
	RETURN VALUE
       The values returned are nonzero if the character c falls into the
       tested class, and zero if not.	*/
int	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}
