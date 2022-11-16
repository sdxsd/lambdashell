/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CODAM C FILE                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire     ########   codam.nl         */
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
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static void	dup_fds(t_cmd *cmd)
{
	if (cmd->i_fd != STDIN_FILENO)
	{
		dup2(cmd->i_fd, STDIN_FILENO);
		close(cmd->i_fd);
	}
	if (cmd->o_fd != STDOUT_FILENO)
	{
		dup2(cmd->o_fd, STDOUT_FILENO);
		close(cmd->o_fd);
	}
}

/* NOTE: INFO */
/* Takes a t_cmd and executes it. */
int	execute_command(t_cmd *cmd)
{
	int	fd;
	int	iter;

	iter = 0;
	// TODO: Allow doing redirecting in & out in the same command
	// TODO: Also do this in execute_builtin()
	if (cmd->redir)
	{
		while (cmd->redir->file[iter] == ' ')
			iter++;
		fd = open(cmd->redir->file + iter, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd <= 0)
			return (msg_err("execute_command()", FAILURE));
		if (cmd->redir->direc == OUTPUT)
			cmd->o_fd = fd;
		if (cmd->redir->direc == INPUT)
			cmd->i_fd = fd;
	}
	dup_fds(cmd);
	if (execve(cmd->path, cmd->args, cmd->env) == -1)
	{
		msg_err("execute_command()", FAILURE);
		dbg_print_cmd(cmd);
		cmd_deallocator(cmd);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	execute_builtin(t_cmd *cmd, t_vector *env)
{
	dup_fds(cmd);
	if (ft_streq(cmd->args[0], "pwd"))
		pwd();
	else if (ft_streq(cmd->args[0], "cd"))
		cd(cmd);
	else if (ft_streq(cmd->args[0], "env"))
		dbg_print_env(env);
	else
		return (FAILURE);
	return (SUCCESS);
}

int	executor(int i_fd, t_exec_element *curr, t_shell *lambda)
{
	int		tube[2];
	pid_t	pid;
	t_cmd	*cmd;
	int		wstatus;

	if (curr->next && pipe(tube) == -1)
		return (msg_err("exec_and_pipe()", FAILURE));
	pid = fork();
	if (pid == FORK_FAILURE)
		return (msg_err("exec_and_pipe()", FAILURE));
	if (pid == FORK_CHILD)
	{
		if (curr->next)
			close(tube[READ]);
		cmd = curr->value;
		if (curr->next)
			cmd->o_fd = tube[WRITE];
		if (i_fd != -1)
			cmd->i_fd = i_fd;
		if (curr->type == tkn_bltin)
			execute_builtin(cmd, lambda->env);
		else
			execute_command(cmd);
	}
	close(i_fd);
	if (curr->next)
		close(tube[WRITE]);
	if (curr->next && executor(tube[READ], curr->next, lambda) != SUCCESS)
		return (msg_err("exec_and_pipe()", FAILURE));
	// TODO: Check if waitpid() options should really be 0
	waitpid(pid, &wstatus, 0);
	if (!curr->next)
		lambda->status = WEXITSTATUS(wstatus);
	return (SUCCESS);
}
