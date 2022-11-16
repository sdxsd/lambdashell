/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CODAM C FILE                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire     ########   codam.nl         */
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
#include <stdlib.h>
#include <unistd.h>

static void	dealloc_lambda(t_shell *lambda)
{
	if (!lambda)
		return ;
	free_vector(lambda->env, dealloc_env_element);
	ft_free(&lambda->line);
}

static int	prompt(t_shell *lambda)
{
	t_exec_element	*exec_list;

	if (lambda->i_tty)
		ps1(lambda);
	lambda->line = readline("λ :: > ");
	if (!lambda->line)
	{
		printf("\n");
		exit(0);
	}
	add_history(lambda->line);
	if (parse_line(lambda) == FAILURE)
		return (FAILURE);
	exec_list = tokenizer(lambda);
	if (exec_list_generator(exec_list, lambda->env) == FAILURE)
	{
		// TODO: Free stuff
		return (FAILURE);
	}
	executor(-1, exec_list, lambda);
	ft_free(&lambda->line);
	return (SUCCESS);
}

static t_shell	*shell_init(char **env)
{
	t_shell		*lambda;

	lambda = ft_calloc(1, sizeof(t_shell));
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
	if (isatty(STDIN_FILENO))
		lambda->i_tty = TRUE;
	else
		lambda->i_tty = FALSE;
	return (lambda);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*lambda;
	int		status;

	// TODO: Why does this continue if argv[0] is NULL?
	if (argc > 1 && argv[0])
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
