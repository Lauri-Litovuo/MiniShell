/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:08:35 by aneitenb          #+#    #+#             */
/*   Updated: 2024/05/31 18:07:32 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	h_handler(int sig)
{
	if (sig == SIGINT)
	{
		// g_signal_code = 2;
		ft_putchar_fd('\n', 1);
		rl_redisplay();
	}
}

void	signals_heredoc(void)
{
	struct sigaction	hsig;

	default_termios();
	ft_memset(&hsig, 0, sizeof(hsig));
	hsig.sa_handler = h_handler;
	sigaction(SIGINT, &hsig, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	c_handler(int sig)
{
	if (sig == SIGINT)
	{
		// g_signal_code = 2;
		ft_putchar_fd('\n', 1);
		// rl_replace_line("",0);
		// rl_on_new_line();
		// rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		// g_signal_code = 3;
		ft_putstr_fd("Quit: 3", 1);
		ft_putchar_fd('\n', 1);
		// rl_replace_line("",0);
		// rl_on_new_line();
		// rl_redisplay();
	}
}

void	signals_child(void)
{
	struct sigaction	childact;

	set_after_termios();
	ft_bzero(&childact, sizeof(childact));
	childact.sa_handler = c_handler;
	sigaction(SIGINT, &childact, NULL);
	sigaction(SIGQUIT, &childact, NULL);
}

void	d_handler(int sig)
{
	// g_signal_code = 2;
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("",0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals_default(void)
{
	struct sigaction	action;
	
	default_termios();
	ft_bzero(&action, sizeof(action));
	action.sa_handler = &d_handler;
	sigaction(SIGINT, &action, NULL);
	signal(SIGQUIT, SIG_IGN);
}