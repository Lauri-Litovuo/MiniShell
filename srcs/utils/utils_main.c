/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:17:37 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/16 12:52:54 by llitovuo         ###   ########.fr       */
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
	if (getenv("HOME=") != NULL)
		ft_strlcpy(arg->home, getenv("HOME="), PATH_MAX);
	if (getenv("HOME=") != NULL)
		ft_strlcpy(arg->home, "/", PATH_MAX);
	return (0);
}
