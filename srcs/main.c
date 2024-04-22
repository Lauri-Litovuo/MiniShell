/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/22 09:22:51 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(int argc, char **argv)
{
	char	*buf;
	size_t	count;
	ssize_t	nread;

	(void)argc;
	(void)argv;
	while (1)
	{
		printf("TheShell$");
		nread = getline(&buf, &count, stdin);
		if (nread == -1)
		{
			free(buf);
			perror ("Exiting shell");
			exit (1);
		}
		printf("User input is: %s", buf);
	}
	free(buf);
	return (0);
}
