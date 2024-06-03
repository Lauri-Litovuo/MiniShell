/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:38:03 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/03 15:32:20 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	check_if_numeric(t_vec *arg_cmd)
{
	int		i;
	char	*ptr;

	i = 0;
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

int	ft_exit(t_exec *exe, t_shell *arg)
{
	int	ret;

	ret = 0;
	printf("exit\n");
	if (arg->count == 1)
	{
		close_fds_exit(arg, 0);
		return (0);
	}
	ret = check_if_numeric(&arg[exe->pos].cmd);
	if (ret != 0)
	{
		close_fds_exit(arg, ret);
		return (ret);
	}
	if (arg->count > 2)
	{
		arg->exit_status = 1;
		error_msg(2, "la_shell: exit: ", "too many arguments\n");
		return (-1);
	}
	return (0);
}
