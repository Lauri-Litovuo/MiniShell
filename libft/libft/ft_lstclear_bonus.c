/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:20:53 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/25 15:28:09 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name: ft_lstclear
	Parameters lst: The address of a pointer to a node.
	del: The address of the function used to delete
	the content of the node.
	Return value: None
	External functs. free
	Description: Deletes and frees the given node and every
	successor of that node, using the function ’del’
	and free(3).
	Finally, the pointer to the list must be set to
	NULL.	*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*previous;

	current = *lst;
	while (current != NULL)
	{
		previous = current;
		current = current->next;
		del(previous->content);
		free(previous);
	}
	*lst = NULL;
}
