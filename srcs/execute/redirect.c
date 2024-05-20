/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:15:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/20 09:38:06 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	reset_fds(t_redir *redir)
{
	int	ret;

	ret = 0;
	if (!redir)
		return (0);
	if (redir->orig_fdin != -1)
	{
		if (dup2(redir->orig_fdin, STDIN_FILENO) == -1)
			ret = -1;
		close (redir->orig_fdin);
		redir->orig_fdin = -1;
	}
	if (redir->orig_fdout != -1)
	{
		if (dup2(redir->orig_fdout, STDIN_FILENO) == -1)
			ret = -1;
		close (redir->orig_fdout);
		redir->orig_fdout = -1;
	}
	return (ret);
}

int	set_fds(t_redir *redir, t_vec *rdrct, int *pipe_fd)
{
	 int	ret;

	 ret = 0;
	 if (!redir)
	 	return (-1);
	redir->orig_fdin = dup(STDIN_FILENO);
	if (redir->orig_fdin == -1)
		return (perror("dup failed"), -1); //
	redir->orig_fdout = dup(STDOUT_FILENO);
	if (redir->orig_fdout == -1)
		return (perror("dup failed"), -1); //
	if (redir->fd_in != -1)
		if (dup2(redir->fd_in, STDIN_FILENO) == -1)
			ret = error_triple_msg(3, "minishell :", "dup2 :", redir->infile); //
	if (redir->fd_out != -1)
		if (dup2(redir->fd_out, STDOUT_FILENO) == -1)
			ret = error_triple_msg(3, "minishell :", "dup2 :", redir->outfile); //
	return (ret);
}

int	check_files_and_fd(t_redir *redir)
{
	if (!redir || (!redir->infile || redir->outfile))
		return (-1);
	if ((redir->infile && redir->fd_in == -1)
		|| (redir->outfile && redir->fd_out == -1))
		return (-1);
	return (0);
}

int	create_pipes(t_exec *exe, size_t pipe_count)
{
	size_t	i;
	int		*fd;

	i = 0;
	while (i < pipe_count)
	{
		fd = malloc(sizeof(fd) * 2);
		if (!fd || pipe(fd) < 0)
		{
			free_exe(exe);
			return (-1);
		}
		exe->pipe_fd = fd;
	}
}

int setup_pipe_fds(t_redir *redir, t_vec *rdrct, int pos)
{
	
}

void	handle_heredoc(t_pipex *cont, char **av)
{
	int		fd;
	char	*buffer;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror("here_doc");
	while (1)
	{
		ft_printf("heredoc> ");
		buffer = get_next_line(0);
		if (buffer == NULL)
			exit (EXIT_FAILURE);
		if (ft_strncmp(av[2], buffer, ft_strlen(buffer) - 1) == 0)
			break ;
		ft_putstr_fd(buffer, fd);
		free(buffer);
	}
	free(buffer);
	close (fd);
	cont->fd_in = open (".heredoc", O_RDONLY);
	if (cont->fd_in < 0)
		unlink(".heredoc");
}

int	do_redirects(t_vec *rdrct, t_redir *redir, int *pipe_fd)
{
	if (rdrct->len == 0)
	{
		return (0);
	}
	
	return (-1);
}
