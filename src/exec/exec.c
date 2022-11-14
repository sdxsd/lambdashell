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

/* NOTE: INFO */
/* Takes a t_cmd and executes it. */
int	execute_command(t_cmd *cmd)
{
	int	fd;
	int	iter;

	iter = 0;
	if (cmd->redir)
	{
		while (cmd->redir->file[iter] == ' ')
			iter++;
		fd = open(cmd->redir->file + iter, O_RDWR);
		if (fd <= 0)
			return (msg_err("execute_command()", FAILURE));
		if (cmd->redir->direc == OUTPUT)
			cmd->o_fd = fd;
		if (cmd->redir->direc == INPUT)
			cmd->i_fd = fd;
	}
		dup2(cmd->i_fd, STDIN_FILENO);
		dup2(cmd->o_fd, STDOUT_FILENO);
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
	dup2(cmd->i_fd, STDIN_FILENO);
	dup2(cmd->o_fd, STDOUT_FILENO);
	if (!ft_strncmp(cmd->args[0], "pwd", 3))
		pwd();
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		cd(cmd, env);
	else if (!ft_strncmp(cmd->args[0], "env", 3))
		dbg_print_env(env);
	else
		return (FAILURE);
	return (SUCCESS);
}

static int	exec_single(t_exec_element *head, t_vector *env)
{
	int	ret;

	if (head->type == tkn_cmd)
	{
		ret = fork();
		if (ret == FORK_FAILURE)
			return (msg_err("exec_single()", FAILURE));
		if (ret == FORK_CHILD)
		{
			if (head->type == tkn_cmd)
				execute_command(head->value);
		}
		waitpid(0, NULL, 0);
	}
	else if (head->type == tkn_bltin)
		execute_builtin(head->value, env);
	return (SUCCESS);
}

int	lnk_cmds(t_exec_element *head, int **pipes)
{
	t_exec_element	*list;
	t_cmd			*cmd;
	int				iter;

	pipes = ft_calloc(sizeof(int *), count_elements(head) - 1);
	if (!pipes)
		return (FAILURE);
	list = head;
	iter = 0;
	while (iter < count_elements(head) - 1)
	{
		if (list->next)
		{
			pipes[iter] = malloc(sizeof(int) * 2);
			if (!pipes[iter])
			{
				dealloc_ptr_array((void **)pipes);
				return (msg_err("lnk_cmds()", FAILURE));
			}
			if (pipe(pipes[iter]) == -1)
			{
				dealloc_ptr_array((void **)pipes);
				return (msg_err("lnk_cmds()", FAILURE));
			}
			cmd = list->value;
			cmd->o_fd = pipes[iter][WRITE];
			printf("CMD_1 O_FD: %d\n", cmd->o_fd);
			cmd = list->next->value;
			cmd->i_fd = pipes[iter][READ];
			printf("CMD_2 i_FD: %d\n", cmd->i_fd);
			iter++;
		}
		list = list->next;
	}
	return (SUCCESS);
}

int	exec_and_pipe(int i_fd, t_exec_element *curr, t_shell *lambda)
{
	int		tube[2];
	int		f_ret;
	t_cmd	*cmd;

	if (i_fd == -1)
		if (pipe(tube) == -1)
			return (msg_err("exec_and_pipe()", FAILURE));
	f_ret = fork();
	if (f_ret == FORK_FAILURE)
		return (msg_err("exec_and_pipe()", FAILURE));
	if (f_ret == FORK_CHILD)
	{
		close(tube[READ]);
		cmd = curr->value;
		cmd->o_fd = tube[WRITE];
		cmd->i_fd = i_fd;
		execute_command(curr->value);
	}
	close(i_fd);
	close(tube[WRITE]);
	if (curr->next)
		if (exec_and_pipe(tube[READ], curr->next, lambda) != SUCCESS)
			return (msg_err("exec_and_pipe()", FAILURE));
	return (SUCCESS);
}

int	executor(t_exec_element *head, t_shell *lambda)
{
	t_exec_element	*list;

	list = head;
	if (!list->next)
		exec_single(head, lambda->env);
	else
		exec_and_pipe(-1, head, lambda);
	return (SUCCESS);
}
