/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneitenb <aneitenb@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:54:58 by aneitenb          #+#    #+#             */
/*   Updated: 2024/06/02 16:14:13 by aneitenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	enabled_termios(void)
{
	struct termios	term;
	
	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
	
void	disabled_termios(void)
{
	struct termios	term;

	ft_bzero(&term, sizeof(term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}