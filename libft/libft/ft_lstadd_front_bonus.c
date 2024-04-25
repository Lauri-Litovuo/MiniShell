/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:48:32 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/25 15:28:08 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name ft_lstadd_front
	Parameters lst: The address of a pointer to the first link of
	a list.
	new: The address of a pointer to the node to be
	added to the list.
	Return value: None
	External functs. None
	Description: Adds the node ’new’ at the beginning of the list.*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
