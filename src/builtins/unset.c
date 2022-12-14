/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 17:15:47 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/09 17:15:47 by sbos          ########   odam.nl         */
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

static int	string_cmp_fn(void *lst_content, void *needle)
{
	return (ft_strcmp(((t_env_element *)lst_content)->key, (char *)needle));
}

// TODO: Should anything special happen if no argument is provided?
t_status	unset(t_cmd *cmd, t_shell *lambda)
{
	char	**args;

	args = cmd->args;
	while (*args)
	{
		// TODO: I think there's a memory leak here since this function doesn't free the content?
		ft_lst_remove_if(&lambda->env, *args, string_cmp_fn);
		args++;
	}
	return (OK);
}
