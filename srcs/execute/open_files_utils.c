/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:35:22 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/12 17:36:48 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	assign_redir_values(t_redir *redir, int fd, char *filename)
{
	redir->infile = filename;
	if (redir->re_pos > redir->hd_pos)
		redir->fd_in = fd;
	redir->file_in = ERRO;
	if (fd == ERRO)
		return (-1);
	redir->file_in = YES;
	return (0);
}