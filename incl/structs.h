/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:26:14 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/11 14:39:32 by aneitenb         ###   ########.fr       */
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
	pid_t	pids;
	t_exec	**exe;
	int		join_flag;
	int		end_flag;
	int		expand_flag;
	int		joinrd_flag;
	int		endrd_flag;
	int		expandrd_flag;
	size_t	split_flag;
	int		exit_code;
}	t_shell;

typedef struct s_vecjoin
{
	char	*base;
	char	*fin;
	int		index;
}	t_vecjoin;

typedef struct s_expd
{
	char	*temp;
	char	*str;
	char	*expanded;
	char	*env_var;
	char	*new;
	char	*join;
	int		ret;
	int		flag;
	size_t	var_len;
	size_t	exp_len;
	size_t	pre_len;
	size_t	total_len;
	size_t	index;
	size_t	ds;
	size_t	i;
	size_t	var_index;
}	t_expd;

#endif