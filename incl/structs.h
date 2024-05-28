/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:26:14 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/27 13:40:29 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_redir
{
	int		fd_in;
	int		fd_out;
	int		orig_fdin;
	int		orig_fdout;
	char	*infile;
	char	*outfile;
	char	*hd_lim;
	char	*hd_file;
	int		pipe_out;
	int		pipe_in;
	int		file_in;
	int		file_out;
	int		hd_in;
	int		hd_pos;
	int		re_pos;
	int		i;
}	t_redir;

typedef struct s_exec
{
	t_redir		redir;
	char		**cmd_argv;
	char		*cmd;
	char		*path;
	int			ret;
	int			*pipe_fd;
	size_t		pos;
}				t_exec;

typedef struct s_shell
{
	t_vec	cmd;
	t_vec	rdrct;
	t_vec	env;
	char	*temp;
	size_t	count;
	size_t	pipe_count;
	size_t	gl_count;
	size_t	i;
	int		j;
	int		*pids;
	t_exec	**exe;
	int		join_flag;
	int		end_flag;
	int		expand_flag;
	int		joinrd_flag;
	int		endrd_flag;
	int		expandrd_flag;
}	t_shell;

typedef struct s_vecjoin
{
	char	*base;
	char	*add;
	char	*fin;
	char	*remainder;
	size_t	base_len;
	size_t	add_len;
	size_t	fin_len;
	int		index;
}	t_vecjoin;

#endif