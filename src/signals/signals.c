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

/* NOTE: Global variable should be defined here. */
int	status;

// Are signals really this simple?: Yes.
//
void	SIGINT_alt(int sig)
{
	if (sig == SIGINT)
		ft_printf("\n");
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n"); // TODO: Should this be printed to stderr?
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		ft_printf("\n"); // TODO: Should this be printed to stderr?
}

void	disable_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_child_set(void)
{
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
}

void	signal_handler_set(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}
