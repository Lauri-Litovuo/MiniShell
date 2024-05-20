/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aidaneitenbach <aidaneitenbach@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:03:03 by aidaneitenb       #+#    #+#             */
/*   Updated: 2024/05/19 22:32:40 by aidaneitenb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void    reset_flags(t_shell *arg)
{
    arg->join_flag = -1;
	arg->end_flag = 0;
	arg->joinrd_flag = -1;
	arg->endrd_flag = 0;
	arg->expand_flag = 0;
}

void    init_s(t_vecjoin *s)
{
    s->base = NULL;
    s->add = NULL;
    s->fin = NULL;
    s->base_len = 0;
    s->add_len = 0;
    s->fin_len = 0;
    s->index = 0;
}

int join_rdrct_vector(t_shell *arg, size_t pos, t_vecjoin *s)
{
    char    *dupped;
    
    s->index = arg->joinrd_flag;
    printf("s index: %d\n", s->index);
    s->base = *(char **)vec_get(&arg[pos].rdrct, arg->joinrd_flag);
    while (arg->joinrd_flag + 1 < arg->endrd_flag)
    {
        s->fin = ft_strjoin(s->base, \
            *(char **)vec_get(&arg[pos].cmd, arg->joinrd_flag + 1));
        s->base = ft_strdup(s->fin);
        if (s->base == NULL)
            return (-1);
        arg->joinrd_flag++;   
    }
    printf("s->fin: %s\n", s->fin);
    dupped = ft_strdup(s->fin);
    if (vec_replace_one(&arg[pos].rdrct, dupped, (size_t)s->index ) < 0)
        return (-1);
    init_s(s);
    return (0);
}

int join_cmd_vector(t_shell *arg, size_t pos, t_vecjoin *s)
{
    s->index = arg->join_flag;
    printf("s index: %d\n", s->index);
    s->base = *(char **)vec_get(&arg[pos].cmd, arg->join_flag);
    while (arg->join_flag + 1 < arg->end_flag)
    {
        s->fin = ft_strjoin(s->base, \
            *(char **)vec_get(&arg[pos].cmd, arg->join_flag + 1));
        s->base = ft_strdup(s->fin);
        if (s->base == NULL)
            return (-1);
        arg->join_flag++;   
    }
    printf("s->fin: %s\n", s->fin);
    if (vec_replace_one(&arg[pos].cmd, s->fin, (size_t)s->index ) < 0)
        return (-1);
    // while (s->index + 1 < arg->endrd_flag)
    // {
    //     if (vec_remove(&arg[pos].cmd, s->index + 1) < 0)
    //         return (-1);
    //     s->index++;
    // }
    // print_vectors(arg);
    init_s(s);
    return (0);
}

int vec_join(t_shell *arg, size_t pos)
{
    t_vecjoin   s;
    int         ret;

    init_s(&s);
    // printf("arg->joinflag: %zu\n", arg->join_flag);
    // printf("arg->joinRDflag: %zu\n", arg->joinrd_flag);
    if (arg->join_flag > -1)
        ret = join_cmd_vector(arg, pos, &s);
    if (arg->joinrd_flag > -1)
        ret = join_rdrct_vector(arg, pos, &s);
    reset_flags(arg);
    return (0);
}
