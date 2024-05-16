/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:08:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/15 15:55:55 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "minishell.h"

typedef struct s_env
{
	t_vec	paths;
	int		*cmd_pos;
}	t_env;

typedef struct s_redir
{
	int		old_fdin;
	int		new_fdin;
	int		old_fdout;
	int		new_fdout;
}	t_redir;

typedef struct s_exec
{
	t_redir		redir;
	t_env		ex_env;
	char		**cmds;
	char		**paths;
	int			exit_code;
	pid_t		*pids;
	int			pipe_fd[2];
	t_vec		*heredocs;
}				t_exec;

/* add_builtin.c*/
int	isit_child_builtin(char *cmd);
int	isit_builtin(char *cmd, int pos);
int	add_builtin(t_vec *paths, char *cmd);
int	isit_parent_builtin(char *cmd);
/* init_piping.c*/
int	init_piping(t_shell *arg, t_exec *exe);
/*redirects.c*/
int	do_redirects(t_vec *rdrct, t_redir *redir, t_vec *heredoc);
/*run_commands.c*/
int	handle_single_arg(t_vec *rdrct, t_exec *exe, t_vec *env, t_shell *arg);


#endif