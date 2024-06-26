/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:05:18 by llitovuo          #+#    #+#             */
/*   Updated: 2024/06/14 13:23:18 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	print_strings(t_vec *args, size_t i, int op_n);
static int	check_for_quotes(char *str);
static int	write_without_quotes(char *str, int *check, int quote);
static int	check_if_only_n(char *str);

int	ft_echo(t_vec *args)
{
	char		**strs;
	size_t		i;
	int			op_n;

	i = 1;
	op_n = 0;
	strs = (char **)args->memory;
	if (args->len == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (i < args->len && ft_strncmp(strs[i], "-n", 2) == 0)
	{
		if (check_if_only_n(strs[i]) == 1)
		{
			op_n = 1;
			i++;
		}
		else
			break ;
	}
	if (i < args->len && print_strings(args, i, op_n) < 0)
		return (-1);
	return (0);
}

static int	check_if_only_n(char *str)
{
	int	i;

	i = 0;
	if (str[i + 2] == '\0')
		return (1);
	while (str[i + 2] != '\0')
	{
		if (str[i + 2] == 'n')
			i++;
		else
			return (-1);
	}
	return (1);
}

static int	print_strings(t_vec *args, size_t i, int op_n)
{
	char	**strs;
	int		check;
	int		quote;

	quote = 0;
	check = 0;
	strs = (char **)args->memory;
	while (i < args->len)
	{
		quote = check_for_quotes(strs[i]);
		if (quote == 0)
			ft_putstr(strs[i], &check);
		else
			write_without_quotes(strs[i], &check, quote);
		if (i < args->len - 1)
			ft_putstr(" ", &check);
		i++;
	}
	if (op_n == 1)
		return (0);
	ft_putstr("\n", &check);
	return (0);
}

static int	check_for_quotes(char *str)
{
	int	count_single;
	int	count_double;

	count_single = 0;
	count_double = 0;
	while (*str)
	{
		if (*str == '\'')
			count_single++;
		if (*str == '\"')
			count_double++;
		str++;
	}
	if (count_single != 0 && count_single % 2 == 0)
		return (1);
	else if (count_double != 0 && count_double % 2 == 0)
		return (2);
	else
		return (0);
	return (0);
}

static int	write_without_quotes(char *str, int *check, int quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (ft_putstr("(null)", check));
	while (str[i])
	{
		if (quote == 2 && str[i] == '\"')
			i++;
		else if (quote == 1 && str[i] == '\'')
			i++;
		else
		{
			count += ft_putchar(str[i], check);
			i++;
		}
	}
	return (count);
}
