/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:33:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/29 09:35:33 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_arg(t_shell *arg, int del_hist)
{
	free (arg);
	if (del_hist == 1)
	{
		//remove history;
	}
}

void	close_fds_exit(t_shell *arg, int ret)
{
	size_t	i;
	t_exec	*exe;

	i = 0;
	if (arg)
	{
		while (i < arg->count)
		{
			exe = arg->exe[i];
			if (exe)
				close_fds(exe, YES);
			i++;
		}
		close_other_pipe_fds(arg, -1);
		free_arg(arg, NO);
	}
	exit (ret);
}