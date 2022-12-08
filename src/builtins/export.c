/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 15:42:21 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/08 15:42:21 by sbos          ########   odam.nl         */
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

static int	argless_export(t_shell *lambda)
{
	t_list			*env_list;
	t_env_element	*env_element;

	// TODO: Should this function ever return FAILURE?
	env_list = lambda->env;
	while (env_list)
	{
		env_element = env_list->content;
		// TODO: This doesn't escape the dollar_in_env export
		ft_printf("declare -x %s=\"%s\"\n", env_element->key, env_element->val);
		env_list = env_list->next;
	}
	return (SUCCESS);
}

static t_env_element	*new_env_element(char *key, char *val)
{
	t_env_element	*env_element;

	env_element = ft_calloc(1, sizeof(*env_element));
	if (env_element)
	{
		env_element->key = key;
		env_element->val = val;
	}
	return (env_element);
}

int	export(t_cmd *cmd, t_shell *lambda)
{
	char			**split;
	t_env_element	*env_element;

	if (!cmd->args)
		return (argless_export(lambda));
	split = ft_split(cmd->args->content, '=');
	if (!split)
	{
		// TODO: Free
		return (FAILURE);
	}
	// TODO: Handle when split[0] or split[1] is NULL
	env_element = new_env_element(split[0], split[1]);
	if (!env_element || !ft_lstnew_back(&lambda->env, env_element))
	{
		// TODO: Free
		return (FAILURE);
	}
	return (SUCCESS);
}
