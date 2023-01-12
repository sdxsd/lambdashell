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

#include "minishell.h"

static t_status	get_val(char **val_ptr, char *env_line)
{
	*val_ptr = NULL;
	if (env_line[get_key_length(env_line)] == '=')
	{
		*val_ptr = ft_strdup(env_line + get_key_length(env_line) + 1);
		if (!*val_ptr)
			return (ERROR);
	}
	return (OK);
}

t_status	add_or_change_env_element(char *env_line, t_list **env_ptr)
{
	char			*key;
	char			*val;
	t_env_element	*env_element;

	key = ft_strndup(env_line, get_key_length(env_line));
	if (!key || get_val(&val, env_line) == ERROR)
		return (ERROR);
	while (*env_ptr)
	{
		env_element = (*env_ptr)->content;
		if (ft_streq(env_element->key, key))
		{
			ft_free(&key);
			if (!val)
				return (OK);
			ft_free(&env_element->val);
			env_element->val = val;
			return (OK);
		}
		env_ptr = &(*env_ptr)->next;
	}
	return (add_env_element(key, val, env_ptr));
}

t_status	init_env(char **env, t_list **lambda_env_ptr)
{
	while (*env)
	{
		if (add_or_change_env_element(*env, lambda_env_ptr) == ERROR)
			return (ERROR);
		env++;
	}
	return (OK);
}

char	*env_get_val(t_list *env, char *key)
{
	t_env_element	*env_element;

	while (env)
	{
		env_element = env->content;
		if (ft_streq(env_element->key, key))
			return (env_element->val);
		env = env->next;
	}
	return (NULL);
}
