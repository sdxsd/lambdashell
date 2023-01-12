/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_variables.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:47:42 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/22 15:47:42 by sbos          ########   odam.nl         */
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

static void	update_state_with_next_character(t_expand_state *expand_state,
				char next_character)
{
	if (is_valid_name_first_chr(next_character))
		expand_state->state = EXPANSION_STATE_VARIABLE;
	else if (next_character == '?')
		expand_state->state = EXPANSION_STATE_STATUS;
	else if (!ft_isspace(next_character) && next_character != '\0')
		expand_state->state = EXPANSION_STATE_INVALID_VARIABLE;
}

static bool	should_get_appended(char *content, t_expansion_state state,
				char *substr_start)
{
	const bool	is_variable_end = \
		state == EXPANSION_STATE_VARIABLE && !is_valid_name_chr(*content);
	const bool	is_status_or_invalid_end = \
		(state == EXPANSION_STATE_STATUS || \
		state == EXPANSION_STATE_INVALID_VARIABLE) && \
		(content - substr_start >= 2) && \
		(content[-2] == '$');

	return (content > substr_start
		&& (*content == '$' || is_variable_end || is_status_or_invalid_end));
}

static char	*get_expanded_string(char *content, t_lambda *lambda)
{
	t_expand_state	state;

	state.state = EXPANSION_STATE_NORMAL;
	state.substr_start = content;
	state.expanded_string = ft_strdup("");
	if (!state.expanded_string)
		return (perror_malloc_null());
	while (*content)
	{
		if (should_get_appended(content, state.state, state.substr_start)
			&& append(content, &state, lambda) == ERROR)
		{
			ft_free(&state.expanded_string);
			return (NULL);
		}
		if (*content == '$')
			update_state_with_next_character(&state, content[1]);
		content++;
	}
	return (strjoin_appended(content, &state, lambda));
}

static bool	can_contain_whitespace(t_token_type type)
{
	return (type == UNQUOTED || type == DOUBLE_QUOTED);
}

t_status	expand_variables(t_list **tokens_ptr, t_lambda *lambda)
{
	t_list	*tokens;
	t_token	*token;
	char	*expanded_string;

	tokens = *tokens_ptr;
	while (tokens)
	{
		token = tokens->content;
		if (can_contain_whitespace(token->type))
		{
			expanded_string = get_expanded_string(token->content, lambda);
			if (!expanded_string)
				return (ERROR);
			ft_free(&token->content);
			token->content = expanded_string;
		}
		tokens = tokens->next;
	}
	return (OK);
}
