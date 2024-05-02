/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:14:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/02 15:44:30 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	goto_dir(char *target, t_vec *env)
{
	if (chdir(target) != 0)
	{
		perror ("cd to target failed");
		return (-1);
	}
	if (update_pwd_env(env, target) < 0)
		return (-1);
	return (0);
}
