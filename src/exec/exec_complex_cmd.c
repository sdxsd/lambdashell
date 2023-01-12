/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_complex_cmd.c                                 :+:    :+:            */
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
#include <errno.h>

static t_status	execute_child(int i_fd, t_list *cmds, t_lambda *lambda,
					int tube[2])
{
	t_cmd	*cmd;

	signal_handler_child_set();
	cmd = cmds->content;
	if (cmds->next)
		close(tube[READ]);
	if (i_fd != -1)
		cmd->input_fd = i_fd;
	if (cmds->next)
		cmd->output_fd = tube[WRITE];
	if (cmd->path && ft_strchr(cmd->path, '/'))
		if (execute_command(cmd, lambda) == ERROR)
			dealloc_and_exit(g_status, lambda);
	if (execute_builtin(cmd, lambda) == ERROR)
		dealloc_and_exit(g_status, lambda);
	exit(g_status);
	return (OK);
}

static t_status	forkxec(int *pid_ptr, int i_fd, t_list *cmds, t_lambda *lambda)
{
	int	t[2];

	if (cmds->next && pipe(t) == -1)
		return (prefixed_perror("execute_complex_command()"));
	*pid_ptr = fork();
	if (*pid_ptr == FORK_FAILURE)
		return (prefixed_perror("fork"));
	if (*pid_ptr == FORK_CHILD)
		if (execute_child(i_fd, cmds, lambda, t) == ERROR)
			dealloc_and_exit(g_status, lambda);
	disable_signals();
	if (cmds->next)
		close(t[WRITE]);
	if (i_fd != -1)
		close(i_fd);
	if (cmds->next && exec_complex_cmd(t[READ], cmds->next, lambda) != OK)
	{
		g_status = 128;
		if (errno != EAGAIN)
			return (prefixed_perror("execute_complex_command()"));
		return (ERROR);
	}
	return (OK);
}

// TODO: Right now only the parent is closing the read end!!
// Double check if this is an issue.
t_status	exec_complex_cmd(int i_fd, t_list *cmds, t_lambda *lambda)
{
	pid_t	pid;
	int		stat_loc;

	if (forkxec(&pid, i_fd, cmds, lambda) == ERROR)
		return (ERROR);
	waitpid(pid, &stat_loc, 0);
	if (!cmds->next)
		g_status = get_wait_status(stat_loc);
	return (OK);
}
