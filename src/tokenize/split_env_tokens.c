/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_env_tokens.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 16:13:50 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/21 16:13:50 by sbos          ########   odam.nl         */
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

static size_t	get_ptr_array_size(void **ptr)
{
	size_t	size;

	size = 0;
	while (*ptr)
	{
		size++;
		ptr++;
	}
	return (size);
}

static int	new_unquoted_token_back(t_list **current_ptr, char *content,
				t_token_type token_type)
{
	t_token	*token;

	token = get_token(token_type, ft_strdup(content));
	if (!token || !ft_lstnew_back(current_ptr, token))
		return (FAILURE);
	return (SUCCESS);
}

int	split_env_tokens(t_list **tokens_ptr)
{
	t_list	*prev;
	t_list	*current;
	t_token	*token;
	t_list	*next;
	char	**split;
	size_t	split_index;
	size_t	split_count;
	t_list	*last_added;

	prev = NULL;
	current = *tokens_ptr;
	while (current)
	{
		token = current->content;
		next = current->next;

		// TODO: Can the ft_strset() be removed?
		if (token->type == UNQUOTED && (*token->content == '\0' || ft_strset(token->content, WHITESPACE_CHARACTERS)))
		{
			split = ft_split_set(token->content, WHITESPACE_CHARACTERS);

			if (!split)
			{
				// TODO: ??
				return (FAILURE);
			}

			current->next = NULL;

			split_index = 0;
			split_count = get_ptr_array_size((void **)split);
			while (split_index < split_count)
			{
				if (
					(split_index > 0 || ft_strchr(WHITESPACE_CHARACTERS, *token->content))
					&& new_unquoted_token_back(&current, " ", WHITESPACE) == FAILURE)
				{
					// TODO: ??
					return (FAILURE);
				}

				if (new_unquoted_token_back(&current, split[split_index], UNQUOTED) == FAILURE)
				{
					// TODO: ??
					return (FAILURE);
				}

				split_index++;
			}

			dealloc_ptr_array(&split);

			if (split_count > 0 && ft_strchr(WHITESPACE_CHARACTERS, token->content[ft_strlen(token->content) - 1]) && new_unquoted_token_back(&current, " ", WHITESPACE) == FAILURE)
			{
				// TODO: ??
				return (FAILURE);
			}

			dealloc_token(&token);

			if (prev)
			{
				if (current->next)
					prev->next = current->next;
				else
					prev->next = next;
			}
			else
			{
				if (current->next)
					*tokens_ptr = current->next;
				else
					*tokens_ptr = next;
			}

			last_added = ft_lstlast(current);

			if (current->next)
			{
				last_added->next = next;
				prev = last_added;
			}

			ft_free(&current);
		}
		else
			prev = current;

		current = next;
	}
	return (SUCCESS);
}

// TODO: REMOVE THIS BACKUP
// {
// 	original_element = current;
// 	current = next;

// 	if (ft_strlen(token->content) > 0 && ft_strchr(WHITESPACE_CHARACTERS, token->content[ft_strlen(token->content) - 1]) && new_unquoted_token_front(&current, " ") == FAILURE)
// 	{
// 		// TODO: ??
// 		return (FAILURE);
// 	}

// 	split = ft_split_set(token->content, WHITESPACE_CHARACTERS);

// 	if (!split)
// 	{
// 		// TODO: ??
// 		return (FAILURE);
// 	}

// 	split_index = get_ptr_array_size((void **)split);
// 	while (split_index > 0)
// 	{
// 		split_index--;

// 		if (split_index + 1 == get_ptr_array_size((void **)split) && new_unquoted_token_front(&current, " ") == FAILURE)
// 		{
// 			// TODO: ??
// 			return (FAILURE);
// 		}

// 		if (new_unquoted_token_front(&current, split[split_index]) == FAILURE)
// 		{
// 			// TODO: ??
// 			return (FAILURE);
// 		}
// 	}

// 	if (ft_strchr(WHITESPACE_CHARACTERS, *token->content) && new_unquoted_token_front(&current, " ") == FAILURE)
// 	{
// 		// TODO: ??
// 		return (FAILURE);
// 	}

// 	dealloc_token(&token);
// 	ft_free(&original_element);

// 	if (prev == NULL)
// 		*tokens_ptr = current;
// 	else
// 		prev->next = current;

// 	prev = first_added_element;
// 	current = next;
// 	// fprintf(stderr, "a\n");
// 	// fflush(NULL);
// }
