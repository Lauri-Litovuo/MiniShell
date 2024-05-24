/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:26:52 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/14 15:17:56 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	**split_env_paths(t_vec *env);
int			prepare_ex_env(t_vec *paths, int *cmd_pos, t_shell *arg, \
char **paths_env);
static void	add_path(t_vec *paths, char *cmd, char **paths_env);
static char	*find_path(char *cmd, char **env_paths);

int	get_exec_paths(t_vec *paths, int *cmd_pos, t_shell *arg, t_vec *env)
{
	char	**paths_env;

	if (arg->count <= 0)
		return (0);
	paths_env = split_env_paths(env);
	if (prepare_ex_env(paths, cmd_pos, arg, paths_env) < 0)
	{
		free_2d_array(paths_env);
		return (-1);
	}
	free_2d_array(paths_env);
	return (0);
}

static char	**split_env_paths(t_vec *env)
{
	char	**paths;
	char	*path_line;
	char	**envp;
	int		i;
	int		len;

	i = 0;
	envp = (char **)env->memory;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
	{
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	len = ft_strlen(envp[i]);
	path_line = ft_substr(envp[i], 5, len);
	if (path_line == NULL)
		return (NULL);
	paths = ft_split(path_line, ':');
	if (!paths)
		return (free(path_line), NULL);
	return (free(path_line), paths);
}

int	prepare_ex_env(t_vec *paths, int *cmd_pos, t_shell *arg, char **paths_env)
{
	size_t	pos;
	int		flag_pos;
	char	**cmd;

	pos = 0;
	while (pos < arg->count)
	{
		cmd = (char **)arg[pos].cmd.memory;
		flag_pos = isit_builtin(cmd[0], pos);
		if (flag_pos >= 0)
		{
			cmd_pos[pos] = flag_pos;
			add_path(paths, cmd[0], paths_env);
		}
		else
		{
			cmd_pos[pos] = flag_pos;
			if (add_builtin(paths, cmd[0]) < 0)
				return (-1);
		}
		pos++;
	}
	return (0);
}

static void	add_path(t_vec *paths, char *cmd, char **paths_env)
{
	char	*path;

	if (paths_env != NULL)
	{
		path = find_path(cmd, paths_env);
		if (path)
		{
			if (vec_push(paths, &path) < 0)
				exit (1);
		}
	}
	else
	{
		path = ft_strdup(cmd);
		if (vec_push(paths, &path) < 0)
			exit (1);
	}
}

static char	*find_path(char *cmd, char **env_paths)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	if (access(cmd, F_OK) == 0)
	{
		full_path = ft_strdup(cmd);
		return (full_path);
	}
	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (NULL);
	while (env_paths[i])
	{
		full_path = ft_strjoin(env_paths[i], temp);
		if (!full_path)
			return (free(temp), NULL);
		if (access(full_path, F_OK) == 0)
			return (free(temp), full_path);
		free(full_path);
		i++;
	}
	free(temp);
	return (NULL);
}
