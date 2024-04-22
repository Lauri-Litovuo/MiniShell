/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:22:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/04/22 10:19:53 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*buf;
	size_t	count;
	ssize_t	nread;

	(void)argc;
	(void)argv;
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
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
		else
			printf ("is not interactive with terminal\n");
	}
	free(buf);
	return (0);
}
