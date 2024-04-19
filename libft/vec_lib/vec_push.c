/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:55:25 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/19 10:59:29 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_push(t_vec *dst, void *src)
{
	if (!src)
		return (1);
	if (!dst)
		return (-1);
	
}

int main(void)
{
    t_vec   t1;
    int     base[] = {1, 2, 3, 4, 5};
    int     expect[] = {2, 4};

    assert(vec_new(&t1, 1, sizeof(int)) > 0);
    vec_push(&t1, &base[1]);
    vec_push(&t1, &base[3]);
    assert(memcmp(t1.memory, expect, sizeof(expect)) == 0);
    vec_free(&t1);
    printf("test_vec_push successful!\n");
}