/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 17:08:36 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/07 17:08:36 by sbos          ########   odam.nl         */
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

// These ones do exit in Bash: `exit 0`, `exit a 2`, `exit a b`
// These ones don't exit in Bash: `exit 4 2`, `exit 4 a`
void	bltin_exit(t_cmd *cmd)
{
	int		exit_status;

	if (!cmd->args[1])
		return (stop_void());
	if (!ft_atoi_safe(cmd->args[1], &exit_status))
	{
		prefixed_error("exit: ");
		print_error(cmd->args[1]);
		print_error(": numeric argument required\n");
		g_status = 255;
		return (stop_void());
	}
	else if (!cmd->args[2])
	{
		g_status = exit_status;
		return (stop_void());
	}
	else
	{
		prefixed_error("exit: too many arguments\n");
		g_status = 1;
	}
}
