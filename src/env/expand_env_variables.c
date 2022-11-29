/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_env_variables.c                             :+:    :+:            */
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

static char	*get_appended(char *content, bool in_env_variable, char *substr_start, t_vector *env)
{
	char	*appended;
	char	*env_key;

	if (in_env_variable)
	{
		env_key = ft_substr(substr_start, 1, content - substr_start - 1);
		if (!env_key)
		{
			// TODO: Error handling
		}

		// TODO: Try to write this function so it can never have an error
		appended = env_get_val(env, env_key);
		ft_free(&env_key);
		if (!appended)
			appended = ft_strdup("");
	}
	else
		appended = ft_substr(substr_start, 0, content - substr_start);
	return (appended);
}

static bool	is_valid_name_chr(char chr)
{
	return (ft_isalpha(chr) || chr == '_');
}

static char	*get_expanded_string(char *content, t_vector *env)
{
	bool	in_env_variable;
	char	*substr_start;
	char	*expanded_string;
	char	*appended;
	char	*old_expanded_string;

	in_env_variable = false;

	substr_start = content;
	expanded_string = ft_calloc(1, sizeof(*expanded_string));
	if (!expanded_string)
	{
		// TODO: Free
		return (NULL);
	}

	while (*content)
	{
		if (*content == '$' || (in_env_variable && !is_valid_name_chr(*content) && !ft_isdigit(*content)))
		{
			if (content > substr_start)
			{
				appended = get_appended(content, in_env_variable, substr_start, env);
				if (!appended)
				{
					// TODO: Error handling
				}
				substr_start = content;

				old_expanded_string = expanded_string;
				expanded_string = ft_strjoin(old_expanded_string, appended);
				ft_free(&old_expanded_string);

				if (!in_env_variable)
					ft_free(&appended);

				if (!expanded_string)
				{
					// TODO: Free
					return (NULL);
				}

				in_env_variable = false;
			}
		}

		if (*content == '$' && is_valid_name_chr(*(content + 1)))
			in_env_variable = true;

		content++;
	}

	appended = get_appended(content, in_env_variable, substr_start, env);
	if (!appended)
	{
		// TODO: Free
		return (NULL);
	}

	old_expanded_string = expanded_string;
	expanded_string = ft_strjoin(old_expanded_string, appended);
	ft_free(&old_expanded_string);

	if (!in_env_variable)
		ft_free(&appended);

	return (expanded_string);
}

int	expand_env_variables(t_list *tokens, t_vector *env)
{
	t_token	*token;
	char	*expanded_string;

	while (tokens)
	{
		token = tokens->content;

		if (token->type == UNQUOTED || token->type == DOUBLE_QUOTED)
		{
			expanded_string = get_expanded_string(token->content, env);
			if (!expanded_string)
			{
				// TODO: Error handling
			}
			ft_free(&token->content);
			token->content = expanded_string;
		}

		tokens = tokens->next;
	}

	return (SUCCESS); // TODO: Use status value
}
