/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:38:03 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/29 12:47:12 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_exit(t_exec *exe, t_shell *arg)
{
	int	ret;

	ret = 0;
	printf("exit\n");
	if (arg->count == 1)
	{
		free_all(arg);
		return (0);
	}
	ret = check_if_numeric(&arg[exe->pos].cmd);
	if (ret != 0)
	{
		free_all(arg);
		return (ret);
	}
	if (arg->count > 2)
	{
		set_return_to(1);
		error_msg(2, "minishell: exit: ", "too many arguments\n");
		return (-1);
	}
	return (0);
}

int	check_if_numeric(t_vec *arg_cmd)
{
	int		i;
	char	*ptr;

	ptr = *(char **)vec_get(arg_cmd, 1);
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
