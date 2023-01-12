/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arg_string_array.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 16:58:21 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/24 16:58:21 by sbos          ########   odam.nl         */
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

char	**get_arg_string_array(t_list *arg_list)
{
	char	**arg_strings;
	char	**arg_strings_start;

	arg_strings = ft_calloc(ft_lstsize(arg_list) + 1,
			sizeof(*arg_strings));
	if (!arg_strings)
		return (perror_malloc_null());
	arg_strings_start = arg_strings;
	if (arg_list->content)
		*arg_strings = ft_strdup(arg_list->content);
	if (!*arg_strings)
	{
		ft_free(&arg_strings);
		return (perror_malloc_null());
	}
	arg_list = arg_list->next;
	arg_strings++;
	while (arg_list)
	{
		*arg_strings = arg_list->content;
		arg_strings++;
		arg_list = arg_list->next;
	}
	*arg_strings = NULL;
	return (arg_strings_start);
}