/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:31:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/23 16:30:05 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//change the prototyping and delete test vector function when parsing is feeding some stuff

static void	create_test_vector(t_vec *args)
{
	char	*temp;

	vec_new(args, 10, sizeof(char *));
	temp = ft_strdup("export");
	vec_push(args, &temp);
	temp = ft_strdup("HELLO=HEY");
	vec_push(args, &temp);
	temp = ft_strdup("HELLOO=HEY");
	vec_push(args, &temp);
}

static void	create_env_test_vector(t_vec *args)
{
	char	*temp;

	vec_new(args, 10, sizeof(char *));
	temp = ft_strdup("env");
	vec_push(args, &temp);
}

int	launch_builtin(t_vec *env, char *buf)
{
	char	**arg_strs;
	t_vec	args; //del when parsing is ready
	t_vec	envi;

	create_test_vector(&args); //del when parsing is ready
	create_env_test_vector(&envi);
	arg_strs = (char **)args.memory;
	for(size_t i = 0; i < args.len; i++)
		printf("args are: %s\n", arg_strs[i]);
	if (ft_strncmp(arg_strs[0], "env", ft_strlen(arg_strs[0])) == 0 || ft_strncmp(buf, "env", ft_strlen(buf)) == 0) //del first part
		ft_env(env, &envi);
	else if (ft_strncmp(arg_strs[0], "pwd", ft_strlen(arg_strs[0])) == 0)
		ft_pwd();
	else if (ft_strncmp(arg_strs[0], "unset", ft_strlen(arg_strs[0])) == 0)
		ft_unset(env, &args);
	else if (ft_strncmp(arg_strs[0], "export", ft_strlen(arg_strs[0])) == 0 && ft_strncmp(buf, "export", ft_strlen(buf)) == 0)
		ft_export(env, &args);
	// else if (ft_strncmp(args, "exit", ft_strlen(args)) == 0)
	// 	ft_exit();
	// else if (ft_strncmp(args, "echo", ft_strlen(args)) == 0)
	// 	ft_echo();
	return (0);
}
