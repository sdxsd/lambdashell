/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
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

static t_status	find_and_run_builtin(t_cmd *cmd, t_lambda *lambda)
{
	if (ft_streq(cmd->path, "cd"))
		g_status = cd(cmd, lambda);
	else if (ft_streq(cmd->path, "echo"))
		g_status = echo(cmd);
	else if (ft_streq(cmd->path, "env"))
		g_status = env(lambda);
	else if (ft_streq(cmd->path, "exit"))
		bltin_exit(cmd);
	else if (ft_streq(cmd->path, "export"))
		g_status = export(cmd, lambda);
	else if (ft_streq(cmd->path, "pwd"))
		g_status = pwd(lambda);
	else if (ft_streq(cmd->path, "unset"))
		g_status = unset(cmd, lambda);
	else if (cmd->path)
	{
		g_status = 127;
		prefixed_error(cmd->path);
		if (env_get_val(lambda->env, "PATH"))
			print_error(": command not found\n");
		else
			print_error(": No such file or directory\n");
		return (ERROR);
	}
	return (OK);
}

t_status	execute_builtin(t_cmd *cmd, t_lambda *lambda)
{
	if (redirections(cmd->redirections, cmd) == ERROR)
	{
		g_status = 1;
		return (ERROR);
	}
	dup2_cmd(cmd);
	return (find_and_run_builtin(cmd, lambda));
}
