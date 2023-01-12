/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
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

static t_status	argless_cd(t_list *env)
{
	char	*home_path;

	home_path = env_get_val(env, "HOME");
	if (!home_path)
		return (prefixed_error("cd: HOME not set\n"));
	if (chdir(home_path) == -1)
		return (prefixed_perror("chdir"));
	return (OK);
}

t_status	cd(t_cmd *cmd, t_lambda *lambda)
{
	if (!cmd->args[1])
	{
		if (argless_cd(lambda->env) == ERROR)
			return (ERROR);
	}
	else if (chdir(cmd->args[1]) == -1)
		return (prefixed_perror("chdir"));
	if (update_cwd(lambda) == ERROR)
		return (ERROR);
	return (OK);
}
