/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/03 13:06:43 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "builtins.h"

/****************************************
*	Standard output formatting: printf	*
*****************************************/
# include <stdio.h>

/************************************************************************
*	Command-line editing: readline, rl_clear_history, rl_on_new_line,	*
*	rl_replace_line, rl_redisplay, add_history 							*
*************************************************************************/
# include "readline/readline.h"
# include "readline/history.h"

/****************************************************************
*	Dynamic memory allocation and deallocation: malloc, free	*
*	Environment variable access: getenv							*
*****************************************************************/
# include <stdlib.h>

/************************************************************************
*	File I/O operations: write, access, open, read, close, 				*
*	Duplication of file descriptors and pipe creation: dup, dup2, pip	*
*	Terminal-related operations: isatty, ttyname, ttyslot, ioctl		*
*************************************************************************/
# include <unistd.h>

/************************************************************
*	Process management: fork, wait, waitpid, wait3, wait4	*
*************************************************************/
# include <sys/types.h>
# include <sys/wait.h>

/************************************************************
*	Signal handling and process termination: 				*
*	signal, sigaction, sigemptyset, sigaddset, kill, exit	*
*************************************************************/
# include <signal.h>

/********************************************************
*	File and directory operations, process execution:	*
*	getcwd, chdir, stat, lstat, fstat, unlink, execve	*
*********************************************************/
# include <sys/stat.h>
# include <fcntl.h>

/********************************************************
*	Directory manipulation: opendir, readdir, closedir	*
*********************************************************/
# include <dirent.h>

/****************************************
*	Error handling: strerror, perror	*
*****************************************/
# include <string.h>

/********************************************
*	Terminal control: tcsetattr, tcgetattr	*
*********************************************/
# include <termios.h>

/********************************************************
*	Terminal handling, cursor movement, and output: 	*
*	tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs	*
*********************************************************/
# include <curses.h>

# include <limits.h>

/****************************
*			MACROS			*
*****************************/
# define SYNTX "minishell: syntax error near unexpected token "
# define SUBSTR "minishell: substr error\n"
# define VECPUSH "minishell: vec_push error\n"
# define VECNEW "minishell: vec_new error\n"
# define UNMATCH "minishell: unexpected EOF while looking for matching "

/************************************
*			SHELL STRUCT			*
*************************************/
typedef struct s_shell
{
	t_vec	cmd;
	t_vec	rdrct;
	char	*temp;
	size_t	count;
	size_t	pipe_count;
	size_t	gl_count;
	size_t	i;
}	t_shell;

int		parse_input(t_shell *arg, char *buf);
int		error_msg(int flag, char *str, char *specifier);
int		error_msg_free(int flag, char *str, char *specifier, t_vec *larg);
/*		scan_utils		*/
/*int		handle_start(char *buf, int i);
int		handle_q(char *buf, int i);
int		handle_qq(char *buf, int i);
int		handle_pipe(char *buf, int i);
int		handle_lessgreat(char *buf, int i);
int		skip_spaces(char *buf, int i);*/
/*		split utils		*/
/*t_shell	split_regular(char *buf, t_shell *arg, size_t pos);
t_shell	split_by_pipe(char *buf, t_shell *arg, size_t pos);*/
int		split_input(char *buf, t_shell *arg, size_t pos, int i);
int		split_rest(char *buf, t_shell *arg, size_t pos);
/* Builtins*/
int		launch_builtin(t_vec *env, char *buf);
int		ft_env(t_vec *env, t_vec *args);
int		ft_pwd(void);
int		ft_unset(t_vec *env, t_vec *args);
int		ft_export(t_vec *env, t_vec *args);
void	print_exports(t_vec *env);
int		find_index_of_env(t_vec *src, char *str);
char	*extract_env_var(char *arg);
int		ft_echo(t_vec *args);

#endif
