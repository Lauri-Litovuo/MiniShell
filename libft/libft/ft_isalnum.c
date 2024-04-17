/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:51:30 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:52:07 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	DESCRIPTION         
    	isalnum() 
		checks for an alphanumeric character; it is equivalent to
    	(isalpha(c) || isdigit(c)).
	RETURN VALUE         
    	The isalnum() and isalnum_l() functions shall return non-zero if
    	c is an alphanumeric character; otherwise, they shall return 0.*/
int	ft_isalnum(int c)
{
	if (c > 47 && c < 58)
		return (1);
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}
