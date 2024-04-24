/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:31:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/24 10:34:06 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

//change the prototyping and delete test vector function when parsing is feeding some stuff

// static void	create_test_vector(t_vec *args)
// {
// 	char	*temp;

// 	vec_new(args, 10, sizeof(char *));
// 	temp = ft_strdup("export");
// 	vec_push(args, &temp);
// 	temp = ft_strdup("HELLO=HEY");
// 	vec_push(args, &temp);
// 	temp = ft_strdup("HELLOO=HEY");
// 	vec_push(args, &temp);
// }


static void	create_test_vector(t_vec *args, char *buf)
{
	char	**temp;
	int		i;

	i = 0;
	temp = ft_split(buf, ' ');
	vec_new(args, 10, sizeof(char *));
	while (temp[i])
	{
		vec_push(args, &temp[i]);
		i++;
	}
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}

int	launch_builtin(t_vec *env, char *buf)
{
	char	**arg_strs;
	t_vec	args; //del when parsing is ready

	create_test_vector(&args, buf); //del when parsing is ready
	arg_strs = (char **)args.memory;
	// for(size_t i = 0; i < args.len; i++)
	// 	printf("args are: %s\n", arg_strs[i]);
	if (ft_strncmp(arg_strs[0], "env", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_env(env, &args);
	else if (ft_strncmp(arg_strs[0], "pwd", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_pwd();
	else if (ft_strncmp(arg_strs[0], "unset", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_unset(env, &args);
	else if (ft_strncmp(arg_strs[0], "export", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_export(env, &args);
	else if (ft_strncmp(arg_strs[0], "echo", ft_strlen(arg_strs[0]) + 1) == 0)
		ft_echo(&args);
	// else if (ft_strncmp(args, "exit", ft_strlen(args)) == 0)
	// 	ft_exit();
	free_2d_array(arg_strs);
	return (0);
}
