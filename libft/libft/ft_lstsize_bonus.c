/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:20:52 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/25 15:28:20 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Function name: ft_lstsize
	Prototype int ft_lstsize(t_list *lst);
	Parameters lst: The beginning of the list.
	Return value: The length of the list
	External functs. None
	Description: Counts the number of nodes in a list.*/
int	ft_lstsize(t_list *lst)
{
	int	length;

	length = 0;
	while (lst != NULL)
	{
		length++;
		lst = lst->next;
	}
	return (length);
}
