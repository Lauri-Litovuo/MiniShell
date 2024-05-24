/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:26:52 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 12:26:14 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static char	**split_env_paths(t_vec *env);
int			prepare_ex_env(t_vec *paths, int *cmd_pos, t_shell *arg, \
char **paths_env);
static void	add_path(t_vec *paths, char *cmd, char **paths_env);
static char	*find_path(char *cmd, char **env_paths);

char	*get_exec_path(char *cmd, t_vec *env)
{
	char	**paths_env;
	char	*temp;

	if (isit_builtin(cmd, 1) == INT_MIN)
	{
		temp = ft_strdup(cmd);
		if (!temp)
			return (NULL);
		return (temp);
	}
	paths_env = split_env_paths(env);
	temp = find_path(cmd, paths_env);
	if (!temp)
	{
		temp = ft_strdup(cmd);
		if (!temp)
			return (NULL);
	}
	free(paths_env);
	return (temp);
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
