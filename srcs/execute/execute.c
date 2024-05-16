/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:45:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/16 10:01:49 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	init_exe(t_exec *exe, size_t count);
static void	init_env_ex(t_env *ex_env, size_t count);

// static void	print_vec(t_vec *vec) //del
// {
// 		for(size_t i = 0; i < vec->len; i++)
// 			printf("ex_env: %s\n", *(char **)vec_get(vec, i));
// }

int	execute(t_shell *arg, t_vec *env)
{
	t_exec	exe;

	init_exe(&exe, arg->count);
	get_exec_paths(&exe.ex_env.paths, exe.ex_env.cmd_pos, arg, env);
	// print_vec(&exe.ex_env.paths); //del
	// for(size_t i = 0; i < arg->count; i++)
	// 	printf("cmdpos %d\n", exe.ex_env.cmd_pos[i]); //del
	if (init_piping(arg, &exe) < -1)
		return (-1);
	free (exe.ex_env.cmd_pos);
	return (0);
}

static void	init_exe(t_exec *exe, size_t count)
{
	exe->pids = ft_calloc((count), sizeof(int));
	if (exe->pids == 0)
		exit (1);
	exe->exit_code = 0;
	exe->pids = 0;
	init_env_ex(&exe->ex_env, count);
}

void	init_env_ex(t_env *ex_env, size_t count)
{
	ex_env->cmd_pos = (int *)malloc(count * sizeof(int));
	if (!ex_env->cmd_pos)
		exit (1);
	if (vec_new(&ex_env->paths, 20, sizeof(char *)) < 0)
		exit(1);
}
