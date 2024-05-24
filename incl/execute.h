/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:08:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 14:33:59 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "minishell.h"

typedef enum e_pipe
{
	YES = 1,
	NO = 0,
	ERRO = (-1)
}	t_pipe;

/* add_builtin.c*/
int		isit_child_builtin(char *cmd);
int		isit_builtin(char *cmd, int pos);
int		add_builtin(t_vec *paths, char *cmd);
int		isit_parent_builtin(char *cmd);
/* init_piping.c
int	init_piping(t_shell *arg, t_exec *exe);*/
/*redirects.c
int	do_redirects(t_vec *rdrct, t_redir *redir, int pipe_fd);*/
/*run_commands.c
int	handle_single_arg(t_vec *rdrct, t_exec *exe, t_vec *env, t_shell *arg);*/
/*execute.c*/
int		execute(t_shell *arg, t_vec *env);
/*heredoc.c*/
int	check_for_heredoc(t_vec *rdrct, t_redir *redir, t_vec *env, size_t count);
/*errors*/
void	print_exec(t_exec **exe);
int		ft_fprintf(int fd, const char *fmt, ...);
int		setup_exe(t_shell *arg);
char	*get_exec_path(char *cmd, t_vec *env);
int	open_files(t_vec *rdrct, t_redir *redir, t_vec *env, size_t count);


#endif