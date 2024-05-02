/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:16:15 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/02 14:37:21 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*copy_homedir(t_vec *env)
{
	char	*home;
	int		index;

	index = find_index_of_env(env, "HOME");
	if (index < 0)
		return (NULL);
	home = ft_strdup(*(char **)vec_get(env, index) + 5);
	if (!home)
		return (NULL);
	return (home);
}

int	goto_home(t_vec *env, char *home)
{
	if (access(home, F_OK) == 0)
	{
		if (chdir(home) != 0)
		{
			perror ("cd to ~ failed");
			return (-1);
		}
		if (update_pwd_env(env, home) < 0)
			return (-1);
	}
	return (0);
}

int	goto_root(t_vec *env)
{
	if (access("/", F_OK) == 0)
	{
		if (chdir("/") != 0)
		{
			perror ("cd to / failed");
			return (-1);
		}
		if (update_pwd_env(env, "/") < 0)
			return (-1);
	}
	return (0);
}

char	*get_parent(char *target)
{
	char	*temp;
	int		dir_count;

	dir_count = 0;
	temp = target;
	while (*temp != '\0')
	{
		if (*temp == '/')
			dir_count++;
		temp++;
	}
	temp = ft_strrchr(target, '/');
	if (!temp)
		return (NULL);
	if (dir_count > 1)
		temp = ft_substr(target, 0, ft_strlen(target) - ft_strlen(temp));
	else
		temp = ft_substr(target, 0, 1);
	if (!temp)
		return (NULL);
	free (target);
	target = temp;
	return (target);
}


void	expand_home(char *target, char *home)
{
	char	*temp;

	temp = ft_strdup(home);
	ft_strjoin(temp, target + 1);
	free (target);
	target = temp;
}
