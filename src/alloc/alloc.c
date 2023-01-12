/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alloc.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 14:45:15 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/13 14:45:15 by sbos          ########   odam.nl         */
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

#include "minishell.h"

t_env_element	*alloc_env_element(void)
{
	return (ft_calloc(1, sizeof(t_env_element)));
}

t_token	*alloc_token(t_token_type type, char *content)
{
	t_token	*token;

	if (!content)
		return (NULL);
	token = ft_calloc(1, sizeof(*token));
	if (!token)
		return (NULL);
	token->type = type;
	token->content = content;
	return (token);
}

t_status	alloc_cmd(t_cmd **cmd_ptr)
{
	*cmd_ptr = ft_calloc(1, sizeof(**cmd_ptr));
	if (!*cmd_ptr)
		return (ERROR);
	(*cmd_ptr)->input_fd = STDIN_FILENO;
	(*cmd_ptr)->output_fd = STDOUT_FILENO;
	return (OK);
}

t_redirect	*alloc_redirect(char *filepath, t_direction direction,
				bool is_ambiguous)
{
	t_redirect	*redirect;

	redirect = ft_calloc(1, sizeof(*redirect));
	if (!redirect)
		return (NULL);
	redirect->filepath = filepath;
	redirect->direction = direction;
	redirect->is_ambiguous = is_ambiguous;
	return (redirect);
}
