/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:27:32 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/14 19:10:45 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	heredoc_fails(t_redir *redir, int fd)
{
	close (fd);
	unlink (redir->hd_file);
	free(redir->hd_file);
	redir->hd_file = NULL;
	return (-1);
}
