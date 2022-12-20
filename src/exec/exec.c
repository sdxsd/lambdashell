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
				- The freedom to improve the program, and release
				your improvements to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include "../../include/minishell.h"
#include <sys/wait.h>
#include <fcntl.h>

static int	get_wait_status(int status)
{
	// TODO: Add unit test for this one
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	// TODO: Probably also need to add this? Check by adding a unit test
	// else if (WIFSTOPPED(status))
	// 	return (WIFSTOPPED(status));
	return (0); // TODO: Is this wanted?
}

static int	execute_simple_command(t_cmd *cmd, t_shell *lambda)
{
	pid_t	pid;
	int		status;

	if (ft_strchr(cmd->path, '/'))
	{
		pid = fork();
		if (pid == FORK_FAILURE)
			return (msg_err("exec_and_pipe()", FAILURE));
		if (pid == FORK_CHILD)
		{
			signal_handler_child_set();
			if (execute_command(cmd, lambda) == FAILURE)
			{
				// TODO: ??
				return (FAILURE);
			}
		}
		disable_signals();
		waitpid(pid, &status, 0);
		lambda->status = get_wait_status(status);
		signal_handler_set();
	}
	else
	{
		if (execute_builtin(cmd, lambda) == FAILURE)
		{
			// TODO: Can this be moved to the end of execute_builtin()?
			dup2(lambda->stdin_fd, STDIN_FILENO);
			dup2(lambda->stdout_fd, STDOUT_FILENO);
			return (FAILURE);
		}

		// TODO: Can this be moved to the end of execute_builtin()?
		// TODO: Should these both *always* happen?
		dup2(lambda->stdin_fd, STDIN_FILENO);
		dup2(lambda->stdout_fd, STDOUT_FILENO);
	}
	return (SUCCESS);
}

static int	execute_child(int input_fd, t_list *cmds, t_shell *lambda, int tube[2])
{
	t_cmd	*cmd;

	cmd = cmds->content;

	if (cmds->next)
		close(tube[READ]);

	// TODO: Why store input_fd and output_fd in cmd when dups can be done immediately?
	if (input_fd != -1)
		cmd->input_fd = input_fd;
	if (cmds->next)
		cmd->output_fd = tube[WRITE];

	if (ft_strchr(cmd->path, '/'))
	{
		if (execute_command(cmd, lambda) == FAILURE)
		{
			// TODO: ??
		}
	}
	else
	{
		if (execute_builtin(cmd, lambda) == FAILURE)
		{
			// TODO: ??
		}
	}
	exit(lambda->status); // TODO: Should anything be freed before this is called?
	return (SUCCESS);
}

static int	execute_complex_command(int input_fd, t_list *cmds, t_shell *lambda)
{
	int		tube[2];
	pid_t	pid;
	int		status;

	if (cmds->next && pipe(tube) == -1)
		return (msg_err("exec_and_pipe()", FAILURE));
	pid = fork();
	if (pid == FORK_FAILURE)
		return (msg_err("exec_and_pipe()", FAILURE));
	if (pid == FORK_CHILD)
	{
		signal_handler_child_set();
		if (execute_child(input_fd, cmds, lambda, tube) == FAILURE)
		{
			// TODO: ??
		}
	}
	disable_signals();
	if (cmds->next)
		close(tube[WRITE]);
	if (input_fd != -1)
		close(input_fd); // TODO: Right now only the parent is closing the read end!!
	if (cmds->next && execute_complex_command(tube[READ], cmds->next, lambda) != SUCCESS)
		return (msg_err("exec_and_pipe()", FAILURE));
	waitpid(pid, &status, 0);
	if (!cmds->next)
		lambda->status = get_wait_status(status);
	return (SUCCESS);
}

int	execute(t_list *cmds, t_shell *lambda)
{
	if (cmds->next)
		return (execute_complex_command(-1, cmds, lambda));
	return (execute_simple_command(cmds->content, lambda));
}
