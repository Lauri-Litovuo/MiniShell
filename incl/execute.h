/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:08:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/12 19:02:27 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "minishell.h"

typedef enum e_pipe
{
	YES = 1,
	NO = 0,
	ERRO = (-1),
	DIRECTORY = 555,
	PERMISSION = 126,
	CMD_NOT_FOUND = 127,
	NO_FILE = 444,
}	t_pipe;

int		isit_builtin(char *cmd, int pos);
int		add_builtin(t_vec *paths, char *cmd);
int		execute(t_shell *arg);
int		check_for_heredoc(t_vec *rdrct, \
		t_redir *redir, t_shell *arg, size_t count);
void	print_exec(t_exec **exe);
int		ft_fprintf(int fd, const char *fmt, ...);
int		setup_exe(t_shell *arg);
char	*get_exec_path(char *cmd, t_vec *env);
int		open_files(t_vec *rdrct, t_exec *exe, t_shell *arg);
int		run_command(t_shell *arg, t_exec *exe);
int		set_fds(t_redir *redir);
int		set_pipe_fds(t_exec *exe, t_shell *arg);
int		check_files_and_fd(t_redir *redir);
void	close_other_pipe_fds(t_shell *arg, size_t pos);
int		reset_fds(int orig_fd[2]);
void	free_arg(t_shell *arg, int del_hist);
void	close_fds(t_exec *exe);
void	close_fds_exit(t_shell *arg, int ret);
void	close_all(t_shell *arg, int pos);
int		execve_error(t_exec *exe, char *err_msg, int ret);
void	file_error(char *filename, char *err_msg, t_redir *redir, int flag);
int		execute_single_builtin(t_shell *arg);
int		assign_redir_values(t_redir *redir, int fd, char *filename);
int		init_redir(t_redir *redir);
int		init_exec(t_exec *exe);
int		split_insert(t_exec *exe, t_shell *arg, size_t i);
int		split_vec(t_exec *exe, t_shell *arg, size_t i, size_t j);

#endif