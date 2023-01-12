/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 17:08:18 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/18 17:08:18 by sbos          ########   odam.nl         */
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

static void	*token_or_lstnew_back_error(t_token **token_ptr,
				t_list **tokens_ptr)
{
	dealloc_token(token_ptr);
	dealloc_lst(tokens_ptr, dealloc_token);
	return (NULL);
}

static void	*content_error(t_list **tokens_ptr)
{
	dealloc_lst(tokens_ptr, dealloc_token);
	return (perror_malloc_null());
}

static void	*unmatched_quote_error(t_list **tokens_ptr)
{
	g_status = 2;
	prefixed_error("unexpected EOF while looking for matching quote\n");
	dealloc_lst(tokens_ptr, dealloc_token);
	return (NULL);
}

static t_token_type	subtokenize(char **line)
{
	if (**line == '\'')
		return (subtokenize_single_quote(line));
	else if (**line == '"')
		return (subtokenize_double_quote(line));
	else if ((**line == '<' && (*line)[1] == '<'))
		return (subtokenize_heredoc(line));
	else if ((**line == '>' && (*line)[1] == '>'))
		return (subtokenize_append(line));
	else if ((**line == '<' || **line == '>'))
		return (subtokenize_redirection(line));
	else if (**line == '|')
		return (subtokenize_pipe(line));
	else if (ft_isspace(**line))
		return (subtokenize_whitespace(line));
	else
		return (subtokenize_unquoted(line));
}

t_list	*tokenize(char *line)
{
	t_list			*tokens;
	char			*old_line_pos;
	t_token_type	token_type;
	char			*content;
	t_token			*token;

	tokens = NULL;
	while (*line)
	{
		old_line_pos = line;
		token_type = subtokenize(&line);
		if (token_type == UNMATCHED_QUOTE)
			return (unmatched_quote_error(&tokens));
		if (token_type == SINGLE_QUOTED || token_type == DOUBLE_QUOTED)
			content = ft_substr(old_line_pos, 1, line - old_line_pos - 2);
		else
			content = ft_substr(old_line_pos, 0, line - old_line_pos);
		if (!content)
			return (content_error(&tokens));
		token = alloc_token(token_type, content);
		if (!token || !ft_lstnew_back(&tokens, token))
			return (token_or_lstnew_back_error(&token, &tokens));
	}
	return (tokens);
}
