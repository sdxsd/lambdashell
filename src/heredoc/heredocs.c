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
Copyright (C) 2022 Will Maguire and Sander Bos

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

static t_status	resolve_and_add_delimiter(t_token *delimiter, t_list *prev,
					t_list *next, t_lambda *lambda)
{
	char	*path;

	path = heredoc(delimiter, lambda);
	ft_free(&delimiter->content);
	if (!path)
		return (ERROR);
	delimiter->content = path;
	delimiter->type = UNQUOTED;
	prev->next = NULL;
	if (!ft_lstnew_back(&prev, delimiter))
	{
		prev->next = next;
		perror_malloc();
		return (dealloc_token(&delimiter));
	}
	return (OK);
}

static t_status	strjoin_to_delimiter(t_token *token, t_token *delimiter)
{
	char	*appended;

	if (token->type == SINGLE_QUOTED || token->type == DOUBLE_QUOTED)
		delimiter->type = DOUBLE_QUOTED;
	if (token->type == UNQUOTED)
		appended = ft_strtrim_whitespace(token->content);
	else
		appended = ft_strdup(token->content);
	delimiter->content = ft_strjoin_and_free_left_right(delimiter->content,
			&appended);
	if (!delimiter->content)
	{
		dealloc_token(&delimiter);
		return (perror_malloc());
	}
	return (OK);
}

static t_status	fill_delimiter(t_list **tokens_ptr, t_token *delimiter,
					t_list **next_ptr)
{
	t_token	*token;

	if (!delimiter || !delimiter->content)
		return (ERROR);
	while ((*tokens_ptr))
	{
		token = (*tokens_ptr)->content;
		if (!is_text_token(token))
			break ;
		if (strjoin_to_delimiter(token, delimiter) == ERROR)
			return (ERROR);
		*next_ptr = (*tokens_ptr)->next;
		dealloc_token(&token);
		*tokens_ptr = *next_ptr;
	}
	return (OK);
}

static void	skip_whitespace_tokens_and_update_prev(t_list **tokens_ptr,
				t_list **prev_ptr)
{
	*tokens_ptr = (*tokens_ptr)->next;
	while (*tokens_ptr
		&& ((t_token *)(*tokens_ptr)->content)->type == WHITESPACE)
	{
		*prev_ptr = *tokens_ptr;
		*tokens_ptr = (*tokens_ptr)->next;
	}
}

t_status	heredocs(t_list *tokens, t_lambda *lambda)
{
	t_token	*token;
	t_list	*prev;
	t_token	*del;
	t_list	*next;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == HEREDOC)
		{
			prev = tokens;
			skip_whitespace_tokens_and_update_prev(&tokens, &prev);
			del = alloc_token(UNQUOTED, ft_strdup(""));
			if (fill_delimiter(&tokens, del, &next) == ERROR)
				return (dealloc_token(&del));
			ft_free(&prev->next);
			prev->next = next;
			if (resolve_and_add_delimiter(del, prev, next, lambda) == ERROR)
				return (dealloc_token(&del));
			prev->next->next = next;
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (OK);
}
