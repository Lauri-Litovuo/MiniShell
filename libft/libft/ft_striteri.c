/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:52:30 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 16:00:51 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	Function name ft_striteri
	Parameters s: The string on which to iterate.
	f: The function to apply to each character.
	Return value None
	External functs. None
	Description Applies the function ’f’ on each character of
	the string passed as argument, passing its index
	as first argument. Each character is passed by address to ’f’ 
	to be modified if necessary	*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))

{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
