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

int	prompt(t_shell *lambda)
{
	t_exec_element	*exec_list;
	lambda->line = readline("λ :: > ");
	if (ft_strlen(lambda->line) < 1)
		return (SUCCESS);
	parse_line(lambda);
	exec_list = tokenizer(lambda);
	exec_list_generator(exec_list, lambda->env);
	dbg_print_exec_list(exec_list);
	executor(exec_list);
	free(lambda->line);
	dealloc_exec_list(exec_list);
	return (SUCCESS);
}

t_shell	*shell_init(char **env)
{
	t_shell		*lambda;

	lambda = malloc(sizeof(t_shell));
	if (!lambda)
		return (NULL);
	lambda->env = init_env(env);
	if (!lambda->env)
	{
		free(lambda);
		return (NULL);
	}
	return (lambda);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*lambda;

	if (argc > 1 && argv[0])
		return (SUCCESS);

	lambda = shell_init(env);
	if (!lambda)
		return (FAILURE);
	dbg_print_env(lambda->env);
	free(lambda);
	return (SUCCESS);

	while (TRUE)
		prompt(lambda);
	return (SUCCESS);
}
