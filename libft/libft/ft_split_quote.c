/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:18:38 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 14:33:52 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	word_count(char *str, t_split *sp, int i)
{
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
		{
			sp->wc++;
			if (str[i] == 39 || str[i] == 34 || str[i] == '{')
				i++;
			if (str[i - 1] == 39 || str[i - 1] == 34)
				while (str[i] && (str[i] != 34 || str[i] != 39))
					i++;
			else if (str[i - 1] == '{' || str[i - 1] == '}')
				while (str[i] && (str[i] != '}' || str[i] != '{'))
					i++;
			else
			{
				while (str[i] && (str[i] != ' '
						&& str[i] != '\t' && str[i] != '\n'))
					i++;
			}
			if (str[i] && (str[i] == 39 || str[i] == 34 || str[i] == '}'))
				i++;
		}
	}
}

char	**init_sp(t_split *sp, char *str)
{
	int	i;

	i = 0;
	sp->i = 0;
	sp->j = 0;
	sp->k = 0;
	sp->wc = 0;
	word_count(str, sp, i);
	sp->array = (char **)malloc(sizeof(char *) * (sp->wc + 1));
	if (sp->array == NULL)
		return (NULL);
	return (sp->array);
}

void	handle_braces(t_split *sp, char *str)
{
	sp->i++;
	while (str[sp->i] && str[sp->i] != '{' && str[sp->i] != '}')
		sp->i++;
	sp->i++;
}

void	scan_str(t_split *sp, char *str)
{
	while (str[sp->i])
	{
		if ((str[sp->i] == ' ' || str[sp->i] == '\t' || str[sp->i] == '\n'))
			str[sp->i] = '!';
		if (str[sp->i] == 39 || str[sp->i] == 34
			|| str[sp->i] == '{' || str[sp->i] == '}')
		{
			if (str[sp->i] == 39 || str[sp->i] == 34)
			{
				str[sp->i] = '!';
				sp->i++;
			}
			if (str[sp->i] == '{' || str[sp->i] == '}')
				handle_braces(sp, str);
			while (str[sp->i] && (str[sp->i] != 39 && str[sp->i] != 34))
				sp->i++;
			if (str[sp->i] == 39 || str[sp->i] == 34)
				str[sp->i] = '!';
		}
		if (str[sp->i])
			sp->i++;
	}
	sp->i = 0;
}

char	**ft_split_quote(char *str)
{
	t_split	sp;
	char	*ptr;

	ptr = str;
	if (init_sp(&sp, str) == NULL)
		return (NULL);
	scan_str(&sp, str);
	while (ptr[sp.i])
	{
		while (ptr[sp.i] && (ptr[sp.i] == '!'))
			sp.i++;
		sp.j = sp.i;
		while (ptr[sp.i] && (ptr[sp.i] != '!'))
			sp.i++;
		if (sp.i > sp.j)
		{
			sp.array[sp.k] = (char *)malloc(sizeof(char) * ((sp.i - sp.j) + 1));
			if (sp.array[sp.k] == NULL)
				return (NULL);
			ft_strncpy(sp.array[sp.k], &ptr[sp.j], sp.i - sp.j);
			sp.k++;
		}
	}
	sp.array[sp.k] = NULL;
	return (sp.array);
}
