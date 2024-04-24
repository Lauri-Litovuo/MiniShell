/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/24 14:18:10 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

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

/****************************
*			MACROS			*
*****************************/
# define SYNTX "minishell: syntax error near unexpected token "
# define SUBSTR "minishell: substr error\n"
# define VECPUSH "minishell: vec_push error\n"
# define VECNEW "minishell: vec_new error\n"

/************************************
*			SHELL STRUCT			*
*************************************/
typedef struct s_shell
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*temp;
}	t_shell;

int		parse_input(t_vec *arg, t_shell *sh, char *buf);
int		error_msg(int flag, char *str, char *specifier);
int		error_msg_free(int flag, char *str, char *specifier, t_vec *larg);
void	init_index(t_shell *sh);

#endif
