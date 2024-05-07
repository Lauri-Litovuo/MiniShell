/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:38:03 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/07 10:10:27 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_exit(t_vec *args)
{
	int	ret;

	ret = 0;
	printf("exit\n");
	if (args->len == 1)
	{
		free_all(args);
		return (0);
	}
	ret = check_if_numeric(args);
	if (ret != 0)
	{
		free_all(args);
		return (ret);
	}
	if (args->len > 2)
	{
		set_return_to(1);
		error_msg(2, "minishell: exit: ", "too many arguments\n");
		return (-1);
	}
}

int	check_if_numeric(t_vec *args)
{
	int		i;
	char	*ptr;

	ptr = *(char **)vec_get(args, 1);
	while (ptr[i])
	{
		if (ft_isdigit(ptr[i]) == 0)
		{
			error_triple_msg(3, "minishell: exit: ", ptr, \
			": numeric argument required\n");
			return (255);
		}
		i++;
	}
	return (0);
}
