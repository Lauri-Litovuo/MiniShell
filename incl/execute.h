/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:08:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/17 13:29:29 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include "minishell.h"

typedef struct s_redir
{
	int		fd_in;
	int		fd_out;
	int		orig_fdin;
	int		orig_fdout;
	char	*infile;
	char	*outfile;
	char	*hd_lim;
}	t_redir;

typedef struct s_exec
{
	t_redir		redir;
	char		**cmd_args;
	char		*cmd;
	char		*path;
	int			ret;
	int			*pipe_fd;
}				t_exec;

/* add_builtin.c*/
int	isit_child_builtin(char *cmd);
int	isit_builtin(char *cmd, int pos);
int	add_builtin(t_vec *paths, char *cmd);
int	isit_parent_builtin(char *cmd);
/* init_piping.c*/
int	init_piping(t_shell *arg, t_exec *exe);
/*redirects.c*/
int	do_redirects(t_vec *rdrct, t_redir *redir, int pipe_fd);
/*run_commands.c*/
int	handle_single_arg(t_vec *rdrct, t_exec *exe, t_vec *env, t_shell *arg);


#endif