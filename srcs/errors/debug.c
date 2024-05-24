/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:34:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 11:02:54 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_exec(t_shell *arg)
{
	size_t	i;
	size_t	j;
	size_t	k;
	t_exec	*temp;
	t_redir	*redir;

	i = 0;
	j = 0;
	k = 0;
	while (i < arg->count)
	{
		j = 0;
		while (j < arg[i].exe.len)
		{
			temp = (t_exec *)vec_get(&arg[i].exe, j);
			printf("arg[%zu], exe[%zu]\n", i, j);
			while (temp->cmd_argv[k] != NULL)
			{
				printf("argv[%zu]: %s\n", k, temp->cmd_argv[k]);
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
			j++;
		}
		i++;
	}
}
