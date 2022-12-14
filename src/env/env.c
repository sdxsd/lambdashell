/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
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

static int	get_key_length(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0' && str[count] != '=')
		count++;
	return (count);
}

int	add_env_element(char *env_line, t_list **env)
{
	t_env_element	*env_element;

	env_element = alloc_env_element();
	if (!env_element)
		return (dealloc_env_element(&env_element));
	env_element->key = ft_strndup(env_line, get_key_length(env_line));
	if (!env_element->key)
		return (dealloc_env_element(&env_element));
	if (env_line[get_key_length(env_line)] == '=')
	{
		env_element->val = ft_strdup(env_line + get_key_length(env_line) + 1);
		if (!env_element->val)
			return (dealloc_env_element(&env_element));
	}
	if (!ft_lstnew_back(env, env_element))
		return (dealloc_env_element(&env_element));
	return (SUCCESS);
}

int	init_env(char **env, t_list **lambda_env)
{
	while (*env)
	{
		if (add_env_element(*env, lambda_env) == FAILURE)
			return (FAILURE);
		env++;
	}
	return (SUCCESS);
}

char	*env_get_val(t_list *env, char *key)
{
	t_env_element	*env_element;

	if (!env || !key)
		return (NULL);
	while (env)
	{
		env_element = env->content;
		// TODO: Can env_element or env_element->key be NULL? ft_streq() below crashes if so
		if (ft_streq(env_element->key, key))
			return (env_element->val);
		env = env->next;
	}
	return (NULL);
}
