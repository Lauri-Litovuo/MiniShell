/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:43:42 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 15:52:34 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	DESCRIPTION
	void *calloc(size_t nelem, size_t elsize);
    The calloc() function shall allocate unused space for an array of
    nelem elements each of whose size in bytes is elsize.  The space
    shall be initialized to all bits 0.
       
	RETURN VALUE
    Upon successful completion with both nelem and elsize non-zero,
    calloc() shall return a pointer to the allocated space. If either
    nelem or elsize is 0, then either:

    *  A null pointer shall be returned and errno may be set to an
        implementation-defined value, or

    *  A pointer to the allocated space shall be returned. The
        application shall ensure that the pointer is not used to
        access an object.

    Otherwise, it shall return a null pointer and set errno to
    indicate the error.		*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	max;

	max = 0 - 1;
	if (count != 0)
		if (max / count < size)
			return (NULL);
	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
