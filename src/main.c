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

static void	prompt(t_shell *lambda)
{
	char	*readline_str;

	if (!lambda->stdin_is_tty)
		rl_outstream = stdin;
	readline_str = get_readline_str(lambda);
	if (!readline_str)
		return ;
	lambda->line = readline(readline_str);
	ft_free(&readline_str);
	if (!lambda->line)
		return (stop_void());
	add_history(lambda->line);
	lambda->tokens = tokenize(lambda->line);
	ft_free(&lambda->line);
	if (check_token_syntax_errors(lambda->tokens) == ERROR)
		return ;
	// dbg_print_tokens(lambda->tokens);
	if (heredocs(lambda->tokens, lambda) == ERROR)
		return ;
	// dbg_print_tokens(lambda->tokens);
	if (expand_variables(&lambda->tokens, lambda) == ERROR)
		return ;
	mark_ambiguous_redirects(lambda->tokens);
	if (whitespace_split_env_tokens(&lambda->tokens) == ERROR)
		return ;
	lambda->cmds = parse(lambda->tokens, lambda);
	if (!lambda->cmds)
		return ;
	// dbg_print_commands(lambda->cmds);
	execute(lambda);
}

static t_status	shell_init(char **env, t_shell *lambda)
{
	signal_handler_set();
	ft_bzero(lambda, sizeof(*lambda));
	status = OK;
	if (init_env(env, &lambda->env) == ERROR)
		return (ERROR);
	if (update_cwd(lambda) == ERROR)
		return (ERROR);
	lambda->stdin_is_tty = isatty(STDIN_FILENO);
	lambda->stdin_fd = dup(STDIN_FILENO);
	lambda->stdout_fd = dup(STDOUT_FILENO);
	if (lambda->stdin_fd == -1 || lambda->stdout_fd == -1)
		return (ERROR);
	return (OK);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	lambda;

	(void)argv;
	if (argc > 1)
		return (ERROR);
	if (shell_init(env, &lambda) == ERROR)
	{
		rl_clear_history();
		return (dealloc_lambda(&lambda));
	}
	while (running())
	{
		prompt(&lambda);
		dealloc_lst(&lambda.tokens, dealloc_token);
		dealloc_lst(&lambda.cmds, dealloc_cmd);
	}
	rl_clear_history();
	dealloc_lambda(&lambda);
	return (status);
}
