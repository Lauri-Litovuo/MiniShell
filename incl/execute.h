/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:08:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/28 14:36:58 by llitovuo         ###   ########.fr       */
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
	DIRECTORY = 126
}	t_pipe;

int		isit_builtin(char *cmd, int pos);
int		add_builtin(t_vec *paths, char *cmd);
int		execute(t_shell *arg);
int		check_for_heredoc(t_vec *rdrct, t_redir *redir, t_vec *env, size_t count);
void	print_exec(t_exec **exe);
int		ft_fprintf(int fd, const char *fmt, ...);
int		setup_exe(t_shell *arg);
char	*get_exec_path(char *cmd, t_vec *env);
int		open_files(t_vec *rdrct, t_exec *exe, t_vec *env);
int		run_command(t_shell *arg, t_exec *exe);

int	set_fds(t_redir *redir);
int	set_pipe_fds(t_exec *exe, t_shell *arg);

int		check_files_and_fd(t_redir *redir);
void	close_other_pipe_fds(t_shell *arg, size_t pos);
int		reset_fds(t_redir *redir);
void	free_arg(t_shell *arg, int del_hist);
void	close_fds(t_exec *exe, int reset);
void	close_fds_exit(t_shell *arg, int ret);
void	close_all(t_shell *arg);



#endif