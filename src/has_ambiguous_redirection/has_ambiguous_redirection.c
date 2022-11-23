/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   has_ambiguous_redirection.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:48:01 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/22 15:48:01 by sbos          ########   odam.nl         */
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

// static bool	has_ambiguous_redirect()
// {
// 	// TODO:
// 	// loop through all tokens of a cmd and when a redirection token has been seen run this:

// 	bool	valid_path = false;
// 	bool	seen_non_space = false;
// 	bool	seen_env_word = false;

// 	char	*content;

// 	while (token->type == WHITESPACE)
// 		token = token->next;

// 	while (token && token->type != WHITESPACE)
// 	{
// 		content = token->content;

// 		if (token->type == UNQUOTED) // && ft_strchr(content, ' '))
// 		{
// 			// Handles:
// 			// `echo a > "foo"$whitespace_left`
// 			if (valid_path && ft_isspace(*content)
// 				return (true);

// 			while (*content)
// 			{
// 				if (ft_isspace(*content))
// 				{
// 					if (seen_non_space)
// 						seen_env_word = true;
// 				}
// 				else
// 				{
// 					valid_path = true;

// 					// Handles:
// 					// `echo a > $whitespace_center`
// 					if (seen_env_word)
// 						return (true);

// 					seen_non_space = true;
// 					break ;
// 				}
// 				content++;
// 			}
// 		}
// 		else
// 		{
// 			valid_path = true;

// 			while (*content)
// 			{
// 				if (!ft_isspace(*content))
// 					// Handles:
// 					// `echo a > $whitespace_right"foo"`
// 					if (seen_env_word)
// 						return (true);

// 					seen_non_space = true;
// 					break ;
// 				}
// 				content++;
// 			}
// 		}

// 		token = token->next;
// 	}

// 	// Handles:
// 	// `echo a > ""`
// 	// `echo a > $empty`
// 	// `echo a > $space`
// 	return (!valid_path)
// }
