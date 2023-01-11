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

static char	*get_appended(char *content, t_expansion_state state, char *substr_start, t_shell *lambda)
{
	char	*appended;
	char	*env_key;
	char	*env_val;

	if (state == EXPANSION_STATE_NORMAL)
		appended = ft_substr(substr_start, 0, content - substr_start);
	else if (state == EXPANSION_STATE_VARIABLE)
	{
		env_key = ft_substr(substr_start, 1, content - substr_start - 1);
		if (!env_key)
		{
			// TODO: Error handling
			return (NULL);
		}
		env_val = env_get_val(lambda->env, env_key);
		ft_free(&env_key);
		if (env_val)
			appended = ft_strdup(env_val);
		else
			appended = ft_strdup("");
	}
	else if (state == EXPANSION_STATE_STATUS)
		appended = ft_itoa(g_status);
	else
		appended = ft_strdup("");
	return (appended);
}

static bool	should_get_appended(char *content, char *substr_start,
				t_expansion_state state)
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

static char	*get_expanded_string(char *content, t_shell *lambda)
{
	t_expansion_state	state;
	char				*substr_start;
	char				*expanded_string;
	char				*appended;

	state = EXPANSION_STATE_NORMAL;
	substr_start = content;
	expanded_string = ft_strdup("");
	if (!expanded_string)
	{
		// TODO: Free
		return (NULL);
	}
	while (*content)
	{
		if (should_get_appended(content, substr_start, state))
		{
			appended = get_appended(content, state, substr_start, lambda);
			if (!appended)
			{
				// TODO: Free
				return (NULL);
			}
			substr_start = content;
			expanded_string = ft_strjoin_and_free_left_right(expanded_string, &appended);
			if (!expanded_string)
			{
				// TODO: Free
				return (NULL);
			}
			state = EXPANSION_STATE_NORMAL;
		}
		if (*content == '$')
		{
			if (is_valid_name_first_chr(*(content + 1)))
				state = EXPANSION_STATE_VARIABLE;
			else if (*(content + 1) == '?')
				state = EXPANSION_STATE_STATUS;
			else if (!ft_isspace(*(content + 1)) && *(content + 1) != '\0')
				state = EXPANSION_STATE_INVALID_VARIABLE;
		}
		content++;
	}
	appended = get_appended(content, state, substr_start, lambda);
	if (!appended)
	{
		// TODO: Free
		return (NULL);
	}
	return (ft_strjoin_and_free_left_right(expanded_string, &appended));
}

t_status	expand_variables(t_list **tokens_list, t_shell *lambda)
{
	t_list	*tokens;
	t_token	*token;
	char	*expanded_string;

	tokens = *tokens_list;
	while (tokens)
	{
		token = tokens->content;
		// TODO: Write. NOTE: What does this mean?
		if (token->type == UNQUOTED || token->type == DOUBLE_QUOTED)
		{
			expanded_string = get_expanded_string(token->content, lambda);
			if (!expanded_string)
			{
				// TODO: Move this dealloc to a parent function.
				// Don't forget that tokens_list might need to be changed to &tokens_list in the parent.
				return (dealloc_lst(tokens_list, dealloc_token));
			}
			ft_free(&token->content);
			token->content = expanded_string;
		}
		tokens = tokens->next;
	}
	return (OK);
}
