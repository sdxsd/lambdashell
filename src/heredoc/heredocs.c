/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredocs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/31 03:42:16 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/31 03:42:16 by sbos          ########   odam.nl         */
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
	- The freedom to improve the program, and release your improvements
	to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include "minishell.h"

t_status	heredocs(t_list *tokens, t_lambda *lambda)
{
	t_token	*token;
	t_list	*prev;
	t_token	*delimiter;
	char	*appended;
	t_list	*next;
	char	*path;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == HEREDOC)
		{
			prev = tokens;
			tokens = tokens->next;
			while (tokens && ((t_token *)tokens->content)->type == WHITESPACE)
			{
				prev = tokens;
				tokens = tokens->next;
			}
			delimiter = alloc_token(UNQUOTED, ft_strdup(""));
			if (!delimiter || !delimiter->content)
			{
				// TODO: Free
				return (dealloc_token(&delimiter));
			}
			// TODO: This is pretty much just get_redirect() from parse.c
			// Try to let this function and that function share this code.
			while (tokens)
			{
				token = tokens->content;
				if (!is_text_token(token))
					break ;
				if (token->type == SINGLE_QUOTED
					|| token->type == DOUBLE_QUOTED)
					delimiter->type = DOUBLE_QUOTED;
				if (token->type == UNQUOTED)
					appended = ft_strtrim_whitespace(token->content);
				else
					appended = ft_strdup(token->content);
				delimiter->content = ft_strjoin_and_free_left_right(delimiter->content, &appended);
				if (!delimiter->content)
				{
					// TODO: Free
					return (ERROR);
				}
				next = tokens->next;
				dealloc_token(&token);
				tokens = next;
			}
			prev->next = next;
			path = heredoc(delimiter, lambda);
			ft_free(&delimiter->content);
			if (!path)
				return (dealloc_token(&delimiter));
			delimiter->content = path;
			delimiter->type = UNQUOTED;
			prev->next = NULL;
			if (!ft_lstnew_back(&prev, delimiter))
			{
				prev->next = next;
				perror_malloc();
				return (dealloc_token(&delimiter));
			}
			prev->next->next = next; // TODO: Can `next` here ever be uninitialized?
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (OK);
}
