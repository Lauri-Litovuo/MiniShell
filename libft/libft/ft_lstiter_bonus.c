/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:33:52 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:51:15 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Function name: ft_lstiter
	Parameters lst: The address of a pointer to a node.
	f: The address of the function used to iterate on
	the list.
	Return value: None
	External functs. None
	Description: Iterates the list ’lst’ and applies the function
	’f’ on the content of each node.	*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	current = lst;
	while (current)
	{
		f(current->content);
		current = current->next;
	}
}
