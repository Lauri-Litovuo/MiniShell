/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/17 12:18:10 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main()		//this is just to check that Makefile and libft work
{
	char	*str = NULL;
	int		res;
	
	res = ft_strlen(str);
	ft_printf("%d\n", res);
	return (1);
}