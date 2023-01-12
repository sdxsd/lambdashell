/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_arg.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 18:15:35 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/12 18:15:35 by sbos          ########   odam.nl         */
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

static char	*get_arg(t_list **tokens_ptr)
{
	char	*arg;
	t_token	*token;

	arg = ft_strdup("");
	if (!arg)
		return (perror_malloc_null());
	while (*tokens_ptr)
	{
		token = (*tokens_ptr)->content;
		if (!is_text_token(token))
			break ;
		arg = ft_strjoin_and_free_left(arg, token->content);
		if (!arg)
			return (perror_malloc_null());
		*tokens_ptr = (*tokens_ptr)->next;
	}
	return (arg);
}

t_status	add_arg(t_list **arg_list_ptr, t_list **tokens_ptr)
{
	char	*arg;

	arg = get_arg(tokens_ptr);
	if (!arg)
		return (ERROR);
	if (!ft_lstnew_back(arg_list_ptr, arg))
	{
		ft_free(&arg);
		return (perror_malloc());
	}
	return (OK);
}
