/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:10 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/16 10:41:08 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* readline: 
Command-line editing: readline, rl_clear_history, rl_on_new_line, 
rl_replace_line, rl_redisplay, add_history */
#include <readline/readline.h>

/*stdio: 
Standard output formatting: printf*/
#include <stdio.h>

/*stdlib:
Dynamic memory allocation and deallocation: malloc, free
Environment variable access: getenv*/
#include <stdlib.h>

/*
unistd: 
File I/O operations: write, access, open, read, close, 
Duplication of file descriptors and pipe creation: dup, dup2, pip
Terminal-related operations: isatty, ttyname, ttyslot, ioctl*/
#include <unistd.h>

/* wait/types:
Process management: fork, wait, waitpid, wait3, wait4*/
#include <sys/types.h>
#include <sys/wait.h>

/*signal: 
Signal handling and process termination: 
signal, sigaction, sigemptyset, sigaddset, kill, exit*/
#include <signal.h>

/* 
Stat & fcntl:
File and directory operations, process execution:
getcwd, chdir, stat, lstat, fstat, unlink, execve*/
#include <sys/stat.h>
#include <fcntl.h>

/*Dirent:
Directory manipulation: opendir, readdir, closedir*/
#include <dirent.h>

/*string:
Error handling: strerror, perror*/
#include <string.h>

/*
termios:
Terminal control: tcsetattr, tcgetattr*/
#include <termios.h>

/*Curses:
Terminal handling, cursor movement, and output: 
tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs*/
#include <curses.h>
