/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:17:37 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/15 23:23:21 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	handle_buf(t_shell *arg)
{
	printf("exit\n");
	free_arg(arg, YES);
	exit (arg->exit_code);
}


int	copy_home(t_shell *arg)
{
	ft_bzero(arg->home, PATH_MAX);
	ft_strlcpy(arg->home, getenv("HOME="), PATH_MAX);
	return (0);
}
