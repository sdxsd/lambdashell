/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

// Are signals really this simple?

// CTRL-c
void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		ft_putstr("Quit");
}

void	disable_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_set(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}
