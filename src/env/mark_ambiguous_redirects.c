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

#include "../../include/minishell.h"

static bool	is_ambiguous_redirect(t_list *tokens)
{
	bool	valid_path;
	bool	seen_filename_start;
	bool	seen_env_word;
	t_token	*token;
	char	*content;

	valid_path = false;
	seen_filename_start = false;
	seen_env_word = false;
	while (tokens && is_text_token(tokens->content))
	{
		token = tokens->content;
		content = token->content;

		if (token->type == UNQUOTED) // && ft_strchr(content, ' '))
		{
			while (*content)
			{
				if (ft_isspace(*content))
				{
					if (seen_filename_start)
						seen_env_word = true;
					// Handles:
					// `echo a > ""$space`
					else if (valid_path)
						valid_path = false;
				}
				else
				{
					valid_path = true;

					seen_filename_start = true;

					// Handles:
					// `echo a > "foo"$whitespace_left`
					// `echo a > $whitespace_center`
					if (seen_env_word)
						return (true);
				}
				content++;
			}
		}
		else
		{
			valid_path = true;

			if (*content)
			{
				seen_filename_start = true;

				// Handles:
				// `echo a > $whitespace_right"foo"`
				if (seen_env_word)
					return (true);
			}
		}

		tokens = tokens->next;
	}

	// Handles:
	// `echo a > ""`
	// `echo a > $empty`
	// `echo a > $space`
	return (!valid_path);
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
