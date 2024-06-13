/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:04:52 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/13 14:10:15 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_cd_struct(t_cd *data)
{
	ft_bzero(data->expand, PATH_MAX);
	ft_bzero(data->home, PATH_MAX);
	ft_bzero(data->path, PATH_MAX);
	ft_bzero(data->target, PATH_MAX);
	ft_bzero(data->cur_dir, PATH_MAX);
	data->ptr = NULL;
	if (data->split_path)
		free_2d_array(data->split_path);
	data->split_path = NULL;
	free (data);
}
