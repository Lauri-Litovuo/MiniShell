/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:08:35 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/06 21:06:13 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	g_signal;

void	h_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 2;
		write(2, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	signals_heredoc(void)
{
	struct sigaction	hact;

	disabled_termios();
	hact.sa_handler = &h_handler;
	sigaction(SIGINT, &hact, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void nl_handler(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	signals_child(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &nl_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	d_handler(int sig)
{
	g_signal = 2;
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("",0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ignore_sigquit(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &action, NULL);
}

void	signals_default(void)
{
	struct sigaction	action;

	ignore_sigquit();
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &d_handler;
	sigaction(SIGINT, &action, NULL);
}
