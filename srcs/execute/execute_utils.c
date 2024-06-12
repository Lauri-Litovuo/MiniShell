/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:57:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/12 16:58:47 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	execute_single_builtin(t_shell *arg)
{
	int	ret;

	ret = 0;
	set_fds(&arg->exe[0]->redir);
	ret = launch_builtin(&arg->env, arg->exe[0], arg);
	close_fds(arg->exe[0]);
	reset_fds(arg->orig_fd);
	arg->exit_code = ret;
	return (ret);
}
