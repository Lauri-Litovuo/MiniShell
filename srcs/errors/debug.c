/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:34:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 14:00:51 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_exec(t_exec **exe)
{
	size_t	i;
	size_t	k;
	t_exec	*temp;
	t_redir	*redir;

	i = 0;
	while (exe[i] != NULL)
	{
		k = 0;
		temp = exe[i];
		printf("\n\nexe[%zu]\n", i);
		while (temp->cmd_argv[k] != NULL)
		{
			printf("argv[%zu]: %s\n", k, temp->cmd_argv[k]);
			k++;
		}
		printf("cmd: %s\n", temp->cmd);
		printf("path: %s\n", temp->path);
		printf("ret: %d\n", temp->ret);
		redir = &temp->redir;
		printf("fd_in: %d\n", redir->fd_in);
		printf("fd_out: %d\n", redir->fd_out);
		printf("orig_fdin: %d\n", redir->orig_fdin);
		printf("orig_fdout: %d\n", redir->orig_fdout);
		printf("hd_pos: %d\n", redir->hd_pos);
		printf("re_pos: %d\n", redir->re_pos);
		printf("pipe_out: %d\n", redir->pipe_out);
		printf("pipe_in: %d\n", redir->pipe_in);
		printf("file_in: %d\n", redir->file_in);
		printf("file_out: %d\n", redir->file_out);
		printf("hd_in: %d\n", redir->hd_in);
		printf("infile: %s\n", redir->infile);
		printf("outfile: %s\n", redir->outfile);
		printf("hd_lim: %s\n", redir->hd_lim);
		printf("hd_file: %s\n", redir->hd_file);
		printf("i: %d\n", redir->i);
		i++;
	}
}
