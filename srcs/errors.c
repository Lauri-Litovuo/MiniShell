/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:59:39 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/02 17:02:03 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	error_msg(int flag, char *str, char *specifier)
{
	if (flag == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(specifier, 2);
	}
	else
	{
		ft_putstr_fd(str, 2);
	}
	return (-1);
}

int	error_msg_free(int flag, char *str, char *specifier, t_vec *vec)
{
	if (flag == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(specifier, 2);
	}
	if (flag == 1)
	{
		ft_putstr_fd(str, 2);
	}
	if (vec)
		vec_free(vec);
	return (-1);
}

