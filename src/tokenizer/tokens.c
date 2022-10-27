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

// NOTE: Returns TRUE if input is a builtin.
int	is_builtin(char *line)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (msg_err("is_builtin()", FAILURE));
	if (!ft_strncmp(split_line[0], "cd", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "echo", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "env", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "export", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "pwd", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "unset", ft_strlen(split_line[0])))
	{
		free_ptr_array(split_line);
		return (TRUE);
	}
	else
	{
		free_ptr_array(split_line);
		return (FALSE);
	}
}

// NOTE: Returns TRUE if input is a command.
int	is_command(char *line, t_vector *env)
{
	char	**split_line;
	char	*path;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (msg_err("is_command()", FAILURE));
	path = get_path(split_line[0], env);
	free_ptr_array(split_line);
	if (!path)
		return (FALSE);
	else
	{
		free(path);
		return (TRUE);
	}
}

// NOTE: Takes line as input and returns type.
int	check_type(char *line, t_vector *env)
{
	if (is_builtin(line) == TRUE)
		return (tkn_bltin);
	else if (is_command(line, env) == TRUE)
		return (tkn_cmd);
	else
		return (msg_err("λ: ", -1));
}

t_exec_element	*tokenizer(t_shell *shell)
{
	t_exec_element	*exec_list;
	t_exec_element	*prev;
	t_exec_element	*curr;
	int				iter;

	iter = 1;
	exec_list = new_exec_element();
	if (!exec_list)
		return (null_msg_err("tokenizer()"));
	exec_list->type = check_type(shell->lines[0], shell->env);
	exec_list->line = shell->lines[0];
	prev = exec_list;
	while (shell->lines[iter])
	{
		curr = new_exec_element();
		if (!curr)
		{
			free_exec_list(exec_list);
			return (null_msg_err("tokenizer()"));
		}
		curr->type = check_type(shell->lines[1], shell->env);
		curr->line = shell->lines[iter];
		prev->next = curr;
		prev = curr;
		iter++;
	}
	return (exec_list);
}
