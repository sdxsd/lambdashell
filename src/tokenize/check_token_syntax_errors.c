/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_token_syntax_errors.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 18:39:48 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/19 18:39:48 by sbos          ########   odam.nl         */
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

static int	check_pipe_syntax_errors(t_list *tokens)
{
	bool	seen_cmd;
	t_token	*token;

	seen_cmd = false;
	while (tokens)
	{
		token = tokens->content;

		if (is_text_token(token))
		{
			seen_cmd = true;
		}

		if (token->type == PIPE && !seen_cmd)
		{
			status = 2;
			ft_putstr_fd(PREFIX": syntax error\n", STDERR_FILENO);
			return (FAILURE);
		}

		if (token->type == PIPE && seen_cmd)
		{
			seen_cmd = false;
		}

		tokens = tokens->next;
	}

	if (!seen_cmd)
	{
		status = 2;
		ft_putstr_fd(PREFIX": syntax error\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_redirection_syntax_errors(t_list *tokens)
{
	bool	seen_redirection;
	t_token	*token;

	seen_redirection = false;
	while (tokens)
	{
		token = tokens->content;

		if (seen_redirection)
		{
			if (token->type != WHITESPACE && !is_text_token(token))
			{
				status = 2;
				ft_putstr_fd(PREFIX": syntax error\n", STDERR_FILENO);
				return (FAILURE);
			}
			else if (is_text_token(token))
				seen_redirection = false;
		}

		if (token->type == REDIRECTION)
		{
			seen_redirection = true;
		}

		tokens = tokens->next;
	}

	if (seen_redirection)
	{
		status = 2;
		ft_putstr_fd(PREFIX": syntax error\n", STDERR_FILENO);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_token_syntax_errors(t_list *tokens)
{
	if (check_pipe_syntax_errors(tokens) == FAILURE)
		return (FAILURE);
	if (check_redirection_syntax_errors(tokens) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
