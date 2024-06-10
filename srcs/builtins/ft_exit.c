/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:38:03 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/10 12:59:31 by aneitenb         ###   ########.fr       */
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
			if ((ptr[i] != '+' && ptr[i] != '-'))
			{
				error_triple_msg(3, "la_shell: exit: ", ptr, \
				": numeric argument required\n");
				return (255);
			}
		}
		i++;
	}
	return (0);
}

static int	get_exit_nbr(t_vec *arg_cmd)
{
	char			*ptr;
	long long int	ret;

	ptr = *(char **)vec_get(arg_cmd, 1);
	if (!ptr)
		return (-1);
	ret = ft_atoi(ptr);
	if (ret < 0)
	{
		ret *= -1;
		ret %= 256;
		ret = 256 - ret;
		return (ret);
	}
	return (ret % 256);
}

int	ft_exit(t_exec *exe, t_shell *arg)
{
	int	ret;
	int	count;

	ret = 0;
	count = arg[exe->pos].cmd.len;
	printf("exit\n");
	if (count == 1)
	{
		close_fds_exit(arg, 0);
		return (0);
	}
	if (count > 2)
	{
		arg->exit_code = 1;
		return (ft_putendl_fd("la_shell: exit: too many arguments", 2), -1);
	}
	ret = check_if_numeric(&arg[exe->pos].cmd);
	if (ret != 0)
	{
		ret = 255;
		close_fds_exit(arg, ret);
	}
	ret = get_exit_nbr(&arg[exe->pos].cmd);
	close_fds_exit(arg, ret);
	return (ret);
}
