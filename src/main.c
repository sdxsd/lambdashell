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

/*
THIS FILE IS LICENSED UNDER THE GNU GPLv3
Copyright (C) 2022  Will Maguire

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>

The definition of Free Software is as follows:
				- The freedom to run the program, for any purpose.
				- The freedom to study how the program works, and adapt it to your needs.
				- The freedom to redistribute copies so you can help your neighbor.
				- The freedom to improve the program, and release
				your improvements to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include "../include/minishell.h"

static int	prompt(t_shell *lambda)
{
	t_list	*tokens;
	char	*readline_str;

	if (!lambda->stdin_is_tty)
		rl_outstream = stdin;
	readline_str = get_readline_str(lambda);
	if (!readline_str)
	{
		dealloc_lambda(lambda);
		return (FAILURE);
	}
	lambda->line = readline(readline_str);
	ft_free(&readline_str);
	if (!lambda->line)
	{
		lambda->exit = true;
		return (SUCCESS);
	}
	add_history(lambda->line);
	tokens = tokenize(lambda->line);
	if (expand_variables(tokens, lambda) == FAILURE)
	{
		// TODO: Freeing
		return (FAILURE);
	}
	// dbg_print_tokens(tokens);
	lambda->cmds = parse(tokens, lambda->env);
	if (!lambda->cmds)
	{
		// TODO: Freeing
		return (FAILURE);
	}
	// dbg_print_commands(lambda->cmds);
	executor(-1, lambda->cmds, lambda);
	ft_free(&lambda->line);
	return (SUCCESS);
}

static int	shell_init(char **env, t_shell *lambda)
{
	ft_bzero(lambda, sizeof(*lambda));
	lambda->status = SUCCESS;
	lambda->exit = FALSE;
	if (init_env(env, &lambda->env) == FAILURE || !lambda->env)
		return (FAILURE);
	// TODO: Should lambda->cwd set by this function be error checked?
	update_cwd(lambda);
	// TODO: May need to check errno afterwards according to man page
	lambda->stdin_is_tty = isatty(STDIN_FILENO);
	lambda->stdin_fd = dup(STDIN_FILENO);
	lambda->stdout_fd = dup(STDOUT_FILENO);
	if (lambda->stdin_fd == -1 || lambda->stdout_fd == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	lambda;
	int		status;

	(void)argv;
	if (argc > 1)
		return (FAILURE);
	if (shell_init(env, &lambda) == FAILURE)
	{
		dealloc_lambda(&lambda);
		return (FAILURE);
	}
	while (!lambda.exit)
		prompt(&lambda);
	status = lambda.status;
	dealloc_lambda(&lambda);
	rl_clear_history();
	return (status);
}
