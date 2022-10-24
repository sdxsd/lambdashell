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

/* NOTE: INFO */
/* Takes a t_cmd and executes it. */
int	execute_command(t_cmd *cmd)
{
	dup2(cmd->i_fd, STDIN_FILENO);
	dup2(cmd->o_fd, STDOUT_FILENO);
	if (execve(cmd->path, cmd->args, cmd->env) == -1)
	{
		msg_err("execute_command()", FAILURE);
		cmd_deallocator(cmd);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	executor(t_exec_element *head)
{
	t_exec_element	*list;
	t_exec_element	*next;
	int				ret;

	list = head;
	if (!list->next)
	{
		ret = fork();
		if (ret == FORK_FAILURE)
			return (msg_err("executor()", FAILURE));
		if (ret == FORK_CHILD)
		{
			if (list->type == tkn_cmd)
				execute_command(list->value);
		}
		waitpid(0, NULL, 0);
		return (SUCCESS);
	}
	while (list->next)
	{
		if (list->type == tkn_pipe)
		{
			next = list->next;
		}
		list = next;
	}
	return (SUCCESS);
}
