/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
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

size_t	get_key_length(char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0' && str[count] != '=')
		count++;
	return (count);
}

t_status	add_env_element(char *key, char *val, t_list **env_ptr)
{
	t_env_element	*env_element;

	env_element = alloc_env_element();
	if (!env_element)
		return (dealloc_env_element(&env_element));
	env_element->key = key;
	env_element->val = val;
	if (!ft_lstnew_back(env_ptr, env_element))
		return (dealloc_env_element(&env_element));
	return (OK);
}

char	**env_to_strings(t_list *env)
{
	char			**env_strings;
	t_env_element	*env_element;
	size_t			index;

	env_strings = ft_calloc(ft_lstsize(env) + 1, sizeof(*env_strings));
	env_strings[ft_lstsize(env)] = NULL;
	if (!env_strings)
		return (NULL);
	index = 0;
	while (env)
	{
		env_element = env->content;
		env_strings[index] = \
			ft_strjoin_array((char *[]){env_element->key, \
										"=", env_element->val, NULL});
		if (!env_strings[index])
		{
			dealloc_ptr_array(&env_strings);
			return (perror_malloc_null());
		}
		env = env->next;
		index++;
	}
	return (env_strings);
}
