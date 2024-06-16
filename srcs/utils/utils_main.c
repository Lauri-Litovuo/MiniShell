/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:17:37 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/16 09:56:40 by aneitenb         ###   ########.fr       */
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
