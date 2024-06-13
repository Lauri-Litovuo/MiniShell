/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_alpha_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:32:28 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/13 13:35:13 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	sort_vec_strings(t_vec *src, int start, int end);
static void	memswap(unsigned char *start, unsigned char *end);
static void	swap_bits(unsigned char *start, unsigned char *end);

void	vec_sort_alpha(t_vec *src)
{
	if (!src || !src->memory)
		return ;
	sort_vec_strings(src, 0, src->len - 1);
}

static void	sort_vec_strings(t_vec *src, int start, int end)
{
	int	temp;
	int	a;
	int	b;

	if (start >= end)
		return ;
	temp = start;
	a = start;
	b = end;
	while (a < b)
	{
		while (a <= end && ft_strncmp(*(char **)vec_get(src, a), \
		*(char **)vec_get(src, temp), \
		ft_strlen(*(char **)vec_get(src, temp))) <= 0)
			a++;
		while (b >= start && ft_strncmp(*(char **)vec_get(src, b), \
		*(char **)vec_get(src, temp), \
		ft_strlen(*(char **)vec_get(src, temp))) > 0)
			b--;
		if (a < b)
			memswap(vec_get(src, a), vec_get(src, b));
	}
	memswap(vec_get(src, temp), vec_get(src, b));
	sort_vec_strings(src, start, b - 1);
	sort_vec_strings(src, b + 1, end);
}

static void	memswap(unsigned char *start, unsigned char *end)
{
	size_t	i;
	size_t	bytes;

	i = 0;
	bytes = sizeof(char *);
	if (!start || !end)
		return ;
	while (i < bytes)
	{
		swap_bits(&start[i], &end[i]);
		i++;
	}
}

static void	swap_bits(unsigned char *start, unsigned char *end)
{
	if (start == end)
		return ;
	*start ^= *end;
	*end ^= *start;
	*start ^= *end;
}
