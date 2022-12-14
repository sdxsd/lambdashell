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

static void	print_env_val(char *env_val, char *env_key)
{
	ft_printf("declare -x %s=\"", env_key);
	while (*env_val != '\0')
	{
		if (*env_val == '$' || *env_val == '\\' || *env_val == '\"')
		{
			ft_printf("\\%c", *env_val);
			env_val++;
		}
		else
		{
			ft_printf("%c", *env_val);
			env_val++;
		}
	}
	ft_putstr("\"\n");
}

static t_status	argless_export(t_shell *lambda)
{
	t_list			*env_list;
	t_env_element	*env_element;

	// TODO: Should this function ever return ERROR?
	env_list = lambda->env;
	while (env_list)
	{
		env_element = env_list->content;
		// TODO: This doesn't escape the dollar_in_env export
		if (env_element->val == NULL)
			ft_printf("declare -x %s\n", env_element->key);
		else
			print_env_val(env_element->val, env_element->key);
		env_list = env_list->next;
	}
	return (OK);
}

static t_status	export_valid_names(char **args, t_list **env_ptr)
{
	t_status	export_status;

	export_status = OK;
	args++;
	while (*args)
	{
		if (!is_valid_identifier(*args))
		{
			prefixed_error("export: ");
			print_error(*args);
			print_error(": not a valid identifier\n");
			export_status = ERROR;
		}
		else
			add_or_change_env_element(*args, env_ptr);
		args++;
	}
	return (export_status);
}

t_status	export(t_cmd *cmd, t_shell *lambda)
{
	if (!cmd->args[1])
		return (argless_export(lambda));
	if (export_valid_names(cmd->args, &lambda->env) == ERROR)
	{
		status = 1;
		return (ERROR);
	}
	/* NOTE: Protect if add_or_change_env_element() goes wrong. */
	/* return (add_or_change_env_element(cmd->args[1], &lambda->env)); */
	return (OK);
}
