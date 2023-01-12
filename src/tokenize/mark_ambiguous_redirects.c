/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mark_ambiguous_redirects.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/28 20:21:22 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/28 20:21:22 by sbos          ########   odam.nl         */
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

// `echo a > ""`
// ambiguous = false;
//
// `echo a > "foo"$whitespace_left`
// state.seen_content = true;
//
// `echo a > $whitespace_right"foo"`
// if (state.seen_word)
static bool	process_quoted(bool *ambiguous, char character,
				t_ambiguous_state *state)
{
	*ambiguous = false;
	if (character)
	{
		state->seen_content = true;
		if (state->seen_word)
			return (true);
	}
	return (false);
}

// `echo a > $space""`
// state.seen_env_space = true;
//
// `echo a > "foo"$whitespace_left`
// if (state.seen_content)
//
// `echo a > ""$space`
// else ambiguous = true;
//
// `echo a > foo`
// ambiguous = false;
//
// `echo a > foo$whitespace_left`
// state.seen_content = true;
//
// `echo a > $whitespace_center`
// if (state.seen_word)
static bool	process_unquoted(char *content, t_ambiguous_state *state,
				bool *ambiguous)
{
	while (*content)
	{
		if (ft_isspace(*content))
		{
			state->seen_env_space = true;
			if (state->seen_content)
				state->seen_word = true;
			else
				*ambiguous = true;
		}
		else
		{
			*ambiguous = false;
			state->seen_content = true;
			if (state->seen_word)
				return (true);
		}
		content++;
	}
	return (false);
}

// `echo a > $space""`
// `echo a > $space""hello`
// if (state.seen_env_space && !state.seen_content)
//
// `echo a > $empty`
// `echo a > $space`
// return (ambiguous);
static bool	is_ambiguous_redirect(t_list *tokens)
{
	bool				ambiguous;
	t_ambiguous_state	state;
	t_token				*token;
	char				*content;

	ambiguous = true;
	state.seen_content = false;
	state.seen_word = false;
	state.seen_env_space = false;
	while (tokens && is_text_token(tokens->content))
	{
		token = tokens->content;
		content = token->content;
		if (token->type == UNQUOTED)
		{
			if (process_unquoted(content, &state, &ambiguous))
				return (true);
		}
		else if (process_quoted(&ambiguous, *content, &state))
			return (true);
		tokens = tokens->next;
	}
	if (state.seen_env_space && !state.seen_content)
		return (true);
	return (ambiguous);
}

void	mark_ambiguous_redirects(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		if (token->type == REDIRECTION)
		{
			tokens = tokens->next;
			skip_whitespace_tokens(&tokens);
			token->is_ambiguous = is_ambiguous_redirect(tokens);
		}
		tokens = tokens->next;
	}
}
