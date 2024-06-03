/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:05:22 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/03 15:28:09 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_cd
{
	char	path[PATH_MAX];
	char	home[PATH_MAX];
	char	target[PATH_MAX];
	char	expand[PATH_MAX];
	char	cur_dir[PATH_MAX];
	char	old_pwd[PATH_MAX];
	char	*ptr;
	char	**split_path;
}			t_cd;

void		init_struct(t_cd *data);
int			launch_builtin(t_vec *env, t_exec *exe, t_shell *arg);
int			ft_env(t_vec *env, t_exec *exe);
int			ft_pwd(t_vec *env);
int			ft_unset(t_vec *env, t_vec *args);
int			ft_export(t_vec *env, t_vec *args);
void		print_exports(t_vec *env);

int			find_index_of_env(t_vec *src, char *str);
int			ft_echo(t_vec *args);
int			ft_exit(t_exec *exe, t_shell *arg);

int			ft_cd(t_vec *env, t_vec *args);
int			goto_path(t_vec *env, t_vec *args, t_cd *data);
int			get_cur_dir(t_vec *env, t_cd *data);
int			get_target_path(t_vec *args, t_cd *data);
int			expand_relative_paths(t_cd *data);
int			copy_homedir(t_vec *env, t_cd *data);
int			goto_home(t_vec *env, t_cd *data);
int			goto_root(t_vec *env);
int			get_parent(t_cd *data, int parent_nbr);
int			expand_home(t_cd *data);
int			goto_dir(t_cd *data, t_vec *env);
void		free_2d_array(char **arr);
void		free_cd_struct(t_cd *data);
int			update_pwd_env(t_vec *env, char	*dir);
int			update_pwd_cd(t_vec *env, t_cd *data);
int			update_old_pwd(t_vec *env, t_cd *data);

#endif