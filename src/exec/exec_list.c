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

#include "../../include/minishell.h"
#include <stdlib.h>

int	count_elements(t_exec_element *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

// NOTE: INFO
// Allocates a new t_exec_element in preparation for use.
t_exec_element	*new_exec_element(void)
{
	t_exec_element	*new;

	new = ft_calloc(1, sizeof(t_exec_element));
	if (!new)
		return (null_msg_err("new_exec_element()"));
	new->type = -1;
	new->line = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

// NOTE: INFO
// Takes an allocated t_exec_element, and a type.
// Allocates and fills out the value of the t_exec_element.
//  +----------------------------------------+
//  | type = cmd                             |
//  | value -> +---------------------------+ |
//  |          | i_fd = STDIN_FILENO       | |
//  |          | o_fd = STDOUT_FILENO      | |
//  |          | args = ("cat" "file.txt") | |
//  |          | env = SHELL_ENV           | |
//  |          | path = "/usr/bin/cat      | |
//  |          | redir = NULL              | |
//  |          +---------------------------+ |
//  | next ->  +----------------+            |
//  |          | t_exec_element |            |
//  |          +----------------+            |
//  +=---------------------------------------+
//
int	exec_list_generator(t_exec_element *head, t_vector *env)
{
	// TODO: Merge cmd_constructor and bltin_constructor()
	if (head->type == tkn_cmd)
	{
		head->value = cmd_constructor(head->line, env);
		if (!head->value)
			return (msg_err("exec_list_generator()", FAILURE));
	}
	if (head->type == tkn_bltin)
	{
		head->value = bltin_constructor(head->line, env);
		if (!head->value)
			return (msg_err("exec_list_generator()", FAILURE));
	}
	if (head->next)
		return (exec_list_generator(head->next, env));
	return (SUCCESS);
}

void	dealloc_exec_list(t_exec_element *head)
{
	// TODO: Why not have bltin_deallocator() called here?
	if (head->type == tkn_cmd)
		cmd_deallocator(head->value);
	if (head->next)
		dealloc_exec_list(head->next);
	ft_free(&head);
}
