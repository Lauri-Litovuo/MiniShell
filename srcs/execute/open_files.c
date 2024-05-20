/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:51:24 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/20 13:17:05 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"


int	get_fdin(t_pipex *cont, char **av)
{
	if (cont->here_doc == 1)
	{
		handle_heredoc(cont, av);
		if (cont->fd_in < 0)
		{
			write (2, "pipex: ", 7);
			perror("heredoc");
			return (-1);
		}
		return (0);
	}
	else
	{
		cont->fd_in = open(av[1], O_RDONLY);
		if (cont->fd_in == -1)
		{
			write (2, "pipex: ", 7);
			perror (av[1]);
			return (-1);
		}
	}
	return (0);
}

int	get_fdout(t_pipex *cont, char **av)
{
	if (cont->here_doc == 1)
		cont->fd_out = open(av[cont->cmd_count + 3], \
		O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		cont->fd_out = open(av[cont->cmd_count + 2], \
		O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (cont->fd_out == -1)
	{
		write (2, "pipex: ", 7);
		if (cont->here_doc == 1)
		{
			perror(av[cont->cmd_count + 3]);
		}
		else
		{
			perror(av[cont->cmd_count + 2]);
		}
		if (cont->fd_in != -1)
			close(cont->fd_in);
		return (-1);
	}
	return (0);
}

int	loop_open_files(t_vec *rdrct, int *file_fds)
{
	int	i;

	i = 0;
	while (i < rdrct->len)
	{
		if (ft_strncmp[])
	}
}

int	open_files(t_shell *args)
{
	char	**ptr;
	int		i;
	int		*file_fds;

	if (args->gl_count == 0)
		return (0);
	file_fds = ft_calloc(args->gl_count, sizeof(int));
	if (!file_fds)
		return (-1); //
	i = 0;
	while (i < args->count)
	{
		if (args[i].rdrct.len == 0)
			i++;
		else
		{
			loop_open_files(&args[i].rdrct, file_fds);
			i++;
		}
	}
}
