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

int	redirections(t_list *list, t_cmd *cmd)
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
			if (list->next)
				creat(redir->file_path, 0644);
			else
			{
				cmd->o_fd = open(redir->file_path, O_CREAT | O_WRONLY, 0644);
				if (cmd->o_fd < 0)
				{
					null_msg_err("redirections()");
					return (FALSE);
				}
			}
		}
		list = list->next;
	}
	return (TRUE);
}

char	**args_to_strings(t_list *args, char *path)
{
	char	**arg_strings;
	int		iter;

	arg_strings = ft_calloc(sizeof(char *), ft_lstsize(args) + 2);
	if (!arg_strings)
		return (null_msg_err("args_to_strings()"));
	arg_strings[0] = path;
	iter = 1;
	while (args)
	{
		arg_strings[iter] = args->content;
		args = args->next;
		iter++;
	}
	arg_strings[iter] = NULL;
	return (arg_strings);
}

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
int	execute_command(t_cmd *cmd, t_vector *env)
{
	char	**env_array;
	char	**arg_array;

	// TODO: Protection!
	redirections(cmd->redirections, cmd);
	env_array = env_to_strings(env);
	arg_array = args_to_strings(cmd->args, cmd->path);
	dup_fds(cmd);
	if (execve(cmd->path, arg_array, env_array) == -1)
	{
		msg_err("execute_command()", FAILURE);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	execute_builtin(t_cmd *cmd, t_vector *env)
{
	char	**arg_strings;

	arg_strings = args_to_strings(cmd->args, cmd->path);
	dup_fds(cmd);
	if (ft_streq(arg_strings[0], "pwd"))
		pwd();
	else if (ft_streq(arg_strings[0], "cd"))
		cd(cmd);
	else if (ft_streq(arg_strings[0], "env"))
		dbg_print_env(env);
	else
		return (FAILURE);
	return (SUCCESS);
}

int	executor(int i_fd, t_list *curr, t_shell *lambda)
{
	int		tube[2];
	pid_t	pid;
	t_cmd	*cmd;
	int		status;

	if (curr->next && pipe(tube) == -1)
		return (msg_err("exec_and_pipe()", FAILURE));
	pid = fork();
	if (pid == FORK_FAILURE)
		return (msg_err("exec_and_pipe()", FAILURE));
	if (pid == FORK_CHILD)
	{
		if (curr->next)
			close(tube[READ]);
		cmd = curr->content;
		if (curr->next)
			cmd->o_fd = tube[WRITE];
		if (i_fd != -1)
			cmd->i_fd = i_fd;
		if (!(ft_strchr(cmd->path, '/')))
			execute_builtin(cmd, lambda->env);
		else
			execute_command(cmd, lambda->env);
	}
	close(i_fd);
	if (curr->next)
		close(tube[WRITE]);
	if (curr->next && executor(tube[READ], curr->next, lambda) != SUCCESS)
		return (msg_err("exec_and_pipe()", FAILURE));
	waitpid(pid, &status, 0);
	if (!curr->next)
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
