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

static int	redirections(t_list *list, t_cmd *cmd)
{
	t_redirect	*redir;
	int			in_encountered;

	in_encountered = FALSE;
	while (list)
	{
		redir = list->content;
		if (redir->direction == DIRECTION_IN && !in_encountered)
		{
			in_encountered = TRUE;
			cmd->i_fd = open(redir->file_path, O_RDONLY);
			if (cmd->i_fd < 0)
			{
				null_msg_err("redirections()");
				return (FALSE);
			}
		}
		else if (redir->direction == DIRECTION_OUT)
		{
			cmd->o_fd = open(redir->file_path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (cmd->o_fd < 0)
			{
				null_msg_err("redirections()");
				return (FALSE);
			}
		}
		list = list->next;
	}
	return (TRUE);
}

static void	dup2_cmd(t_cmd *cmd)
{
	dup2(cmd->i_fd, STDIN_FILENO);
	if (cmd->i_fd != STDIN_FILENO)
		close(cmd->i_fd);

	dup2(cmd->o_fd, STDOUT_FILENO);
	if (cmd->o_fd != STDOUT_FILENO)
		close(cmd->o_fd);
}

static int	execute_command(t_cmd *cmd, t_list *env)
{
	char	**env_array;

	// TODO: Protection!
	redirections(cmd->redirections, cmd);
	// TODO: Try to find a way to not call this env_to_strings() every time
	env_array = env_to_strings(env);
	dup2_cmd(cmd);
	if (execve(cmd->path, cmd->args, env_array) == -1)
	{
		msg_err("execute_command()", FAILURE);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	execute_builtin(t_cmd *cmd, t_shell *lambda)
{
	dup2_cmd(cmd);
	// TODO: Maybe if-statement check whether path or args or args[0] or args[1] is NULL?
	if (ft_streq(cmd->path, "cd"))
		return (cd(cmd, lambda));
	else if (ft_streq(cmd->path, "env"))
		return (env(lambda));
	else if (ft_streq(cmd->path, "exit"))
	{
		// TODO: create define rather than using (2)
		bltin_exit(cmd, lambda);
		return (2);
	}
	else if (ft_streq(cmd->path, "export"))
		return (export(cmd, lambda));
	else if (ft_streq(cmd->path, "pwd"))
		return (pwd(lambda));
	return (FAILURE);
}

int	executor(int i_fd, t_list *cmds, t_shell *lambda)
{
	int		tube[2];
	pid_t	pid;
	t_cmd	*cmd;
	int		status;

	if (cmds->next && pipe(tube) == -1)
		return (msg_err("exec_and_pipe()", FAILURE));
	cmd = cmds->content;

	if (ft_strchr(cmd->path, '/'))
	{
		// TODO: Maybe we shouldn't fork if there is only a single non-builtin command
		pid = fork();
		if (pid == FORK_FAILURE)
			return (msg_err("exec_and_pipe()", FAILURE));
		if (pid == FORK_CHILD)
		{
			if (cmds->next)
				close(tube[READ]);

			if (i_fd != -1)
				cmd->i_fd = i_fd;
			if (cmds->next)
				cmd->o_fd = tube[WRITE];

			execute_command(cmd, lambda->env);
		}
	}
	else
	{
		// TODO: Why store i_fd and o_fd in cmd when dups can be done immediately?
		if (i_fd != -1)
			cmd->i_fd = i_fd;
		if (cmds->next)
			cmd->o_fd = tube[WRITE];

		// TODO: Should this really always be setting lambda->status, unlike non-builtins?
		lambda->status = execute_builtin(cmd, lambda);

		dup2(lambda->stdin_fd, STDIN_FILENO);
		dup2(lambda->stdout_fd, STDOUT_FILENO);
	}
	if (cmds->next)
		close(tube[WRITE]);
	if (i_fd != -1)
		close(i_fd); // TODO: Right now only the parent is closing the read end!!

	if (cmds->next && executor(tube[READ], cmds->next, lambda) != SUCCESS)
		return (msg_err("exec_and_pipe()", FAILURE));
	if (ft_strchr(cmd->path, '/'))
		waitpid(pid, &status, 0);
	if (!cmds->next)
	{
		// TODO: Add unit test for this one
		if (WIFEXITED(status))
			lambda->status = WEXITSTATUS(status);

		else if (WIFSIGNALED(status))
			lambda->status = WTERMSIG(status);

		// TODO: Probably also need to add this? Check by adding a unit test
		// else if (WIFSTOPPED(status))
		// 	lambda->status = WIFSTOPPED(status);
	}
	return (SUCCESS);
}
