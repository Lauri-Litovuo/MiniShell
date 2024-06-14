/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:08:35 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/14 19:17:34 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
	ft_memset(&hact, 0, sizeof(hact));
	sigemptyset(&hact.sa_mask);
	hact.sa_handler = &h_handler;
	sigaction(SIGINT, &hact, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_child(void)
{
	struct sigaction	act;

	enabled_termios();
	ft_memset(&act, 0, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	d_handler(int sig)
{
	g_signal = 2;
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals_default(void)
{
	struct sigaction	action;

	disabled_termios();
	ft_memset(&action, 0, sizeof(action));
	sigemptyset(&action.sa_mask);
	action.sa_handler = &d_handler;
	sigaction(SIGINT, &action, NULL);
	signal(SIGQUIT, SIG_IGN);
}
