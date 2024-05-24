/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:08:42 by llitovuo          #+#    #+#             */
/*   Updated: 2024/05/24 10:14:08 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	put_string(char *str, int *ret, int fd)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		*ret += write(fd, str, 1);
		str++;
	}
}

void	put_digit(long long int num, int base, int *ret, int fd)
{
	char	hex[16];

	*hex = "0123456789abcdef";
	if (num < 0)
	{
		num *= -1;
		*ret += write(fd, "-", 1);
	}
	if (num >= base)
		put_digit ((num / base), base, ret, fd);
	*ret += write(fd, &hex[num % base], 1);
}

int	ft_fprintf(int fd, const char *fmt, ...)
{
	int		ret;
	va_list	ap;

	ret = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%' && (*(fmt + 1) == 's'
				|| *(fmt + 1) == 'd' || *(fmt + 1) == 'x'))
		{
			fmt++;
			if (*fmt == 's')
				put_string(va_arg(ap, char *), &ret, fd);
			if (*fmt == 'd')
				put_digit((long long int)va_arg(ap, int), 10, &ret, fd);
			if (*fmt == 'x')
				put_digit
				((long long int)va_arg(ap, unsigned int), 16, &ret, fd);
		}
		else
			ret += write (1, fmt, 1);
		fmt++;
	}
	va_end(ap);
	return (ret);
}
