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
	t_list	*cmds;

	if (lambda->stdin_is_tty)
	{
		readline_str = get_readline_str(lambda);
		if (!readline_str)
		{
			// TODO: Free
			return (FAILURE);
		}
		lambda->line = readline(readline_str);
	}
	else
	{
		rl_outstream = stdin;
		lambda->line = readline(NULL);
	}
	if (!lambda->line)
	{
		lambda->exit = true;
		return (SUCCESS);
	}
	add_history(lambda->line);
	// if (lambda->line[0]) // TODO: Maybe use?
	tokens = tokenize(lambda->line);
	if (expand_env_variables(tokens, lambda->env) == FAILURE)
	{
		// TODO: Freeing
		return (FAILURE);
	}
	dbg_print_tokens(tokens);
	cmds = parse(tokens, lambda->env);
	if (!cmds)
	{
		// TODO: Freeing
		return (FAILURE);
	}
	dbg_print_commands(cmds);
	// executor(-1, cmds, lambda);
	ft_free(&lambda->line);
	return (SUCCESS);
}

static t_shell	*shell_init(char **env)
{
	t_shell		*lambda;

	lambda = ft_calloc(1, sizeof(*lambda));
	if (!lambda)
		return (NULL);
	lambda->status = SUCCESS;
	lambda->exit = FALSE;
	lambda->env = init_env(env);
	if (!lambda->env)
	{
		ft_free(&lambda);
		return (NULL);
	}
	lambda->stdin_is_tty = isatty(STDIN_FILENO);
	return (lambda);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*lambda;
	int		status;

	(void)argv;
	if (argc > 1)
		return (FAILURE);
	lambda = shell_init(env);
	if (!lambda)
	{
		dealloc_lambda(lambda);
		return (FAILURE);
	}
	while (!lambda->exit)
		prompt(lambda);
	status = lambda->status;
	dealloc_lambda(lambda);
	rl_clear_history();
	return (status);
}
