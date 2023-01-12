/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   whitespace_split_tokens.c                          :+:    :+:            */
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
	- The freedom to improve the program, and release your improvements
	to the public, so that the whole community benefits.
A program is free software if users have all of these freedoms.
*/

#include "minishell.h"

static void	update_prev_pointer_to_next(t_list *prev, t_list *current,
				t_list *next, t_list **tokens_ptr)
{
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
}

static void	update_pointers(t_list *current, t_list **prev, t_list *next,
					t_list **tokens_ptr)
{
	t_list	*last_added;

	update_prev_pointer_to_next(*prev, current, next, tokens_ptr);
	last_added = ft_lstlast(current);
	if (current->next)
	{
		last_added->next = next;
		*prev = last_added;
	}
	ft_free(&current);
}

t_status	whitespace_split_tokens(t_list **tokens_ptr)
{
	t_list	*prev;
	t_list	*current;
	t_token	*token;
	t_list	*next;

	prev = NULL;
	current = *tokens_ptr;
	while (current)
	{
		token = current->content;
		next = current->next;
		if (token->type == UNQUOTED
			&& ft_str_not_set(token->content, WHITESPACE_CHARACTERS))
		{
			current->next = NULL;
			if (split_and_add_spaced_tokens(token, current) == ERROR)
				return (ERROR);
			update_pointers(current, &prev, next, tokens_ptr);
		}
		else
			prev = current;
		current = next;
	}
	return (OK);
}
