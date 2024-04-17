/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:19:31 by aneitenb          #+#    #+#             */
/*   Updated: 2024/04/16 14:36:53 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	print_arguments(const char *format, va_list args, int *check)
{
	if (*format == 'c')
		return (ft_putchar(va_arg(args, int), check));
	else if (*format == 's')
		return (ft_putstr(va_arg(args, char *), check));
	else if (*format == 'p')
		return (ft_putptr(va_arg(args, void *), check));
	else if (*format == 'u')
		return (ft_putun(va_arg(args, unsigned int), check));
	else if (*format == 'd')
		return (ft_putnbr(va_arg(args, int), check));
	else if (*format == 'i')
		return (ft_putnbr(va_arg(args, int), check));
	else if (*format == 'x')
		return (ft_puthexbase(va_arg(args, unsigned int), 0, check));
	else if (*format == 'X')
		return (ft_puthexbase(va_arg(args, unsigned int), 1, check));
	else
		return (ft_putchar(*format, check));
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		check;
	va_list	args;

	count = 0;
	check = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += print_arguments(format, args, &check);
		}
		else
			count += ft_putchar(*format, &check);
		format++;
		if (check == -1)
		{
			va_end(args);
			return (-1);
		}
	}
	va_end(args);
	return (count);
}
