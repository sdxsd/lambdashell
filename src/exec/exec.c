/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
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
	- The freedom to improve the program, and release your improvements
	to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include "minishell.h"
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

t_status	execute_command(t_cmd *cmd, t_lambda *lambda)
{
	char	**env_array;

	if (redirections(cmd->redirections, cmd) == ERROR)
	{
		g_status = 1;
		return (ERROR);
	}
	env_array = env_to_strings(lambda->env);
	dup2_cmd(cmd);
	if (execve(cmd->path, cmd->args, env_array) == -1)
	{
		g_status = 127;
		return (prefixed_perror(cmd->path));
	}
	return (OK);
}

// TODO: Check for memory leak in child processes.
static t_status	forkxec_simp(int *pid, t_cmd *cmd, t_lambda *lambda)
{
	int		stat_loc;

	*pid = fork();
	if (*pid == FORK_FAILURE)
		return (prefixed_perror("execute_simple_command()"));
	if (*pid == FORK_CHILD)
	{
		signal_handler_child_set();
		if (execute_command(cmd, lambda) == ERROR)
			dealloc_and_exit(g_status, lambda);
	}
	disable_signals();
	waitpid(*pid, &stat_loc, 0);
	g_status = get_wait_status(stat_loc);
	signal_handler_set();
	return (OK);
}

static t_status	execute_simple_command(t_cmd *cmd, t_lambda *lambda)
{
	pid_t	pid;

	if (cmd->path && ft_strchr(cmd->path, '/'))
		forkxec_simp(&pid, cmd, lambda);
	else
	{
		if (execute_builtin(cmd, lambda) == ERROR)
		{
			dup2(lambda->stdin_fd, STDIN_FILENO);
			dup2(lambda->stdout_fd, STDOUT_FILENO);
			return (ERROR);
		}
		dup2(lambda->stdin_fd, STDIN_FILENO);
		dup2(lambda->stdout_fd, STDOUT_FILENO);
	}
	return (OK);
}

t_status	execute(t_lambda *lambda)
{
	if (lambda->cmds->next)
		return (exec_complex_cmd(-1, lambda->cmds, lambda));
	return (execute_simple_command(lambda->cmds->content, lambda));
}
