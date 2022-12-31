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
#include <errno.h>

static t_status	redirections(t_list *list, t_cmd *cmd)
{
	t_redirect	*redir;
	int			flags;
	bool		in_encountered;
	int			open_fd;

	in_encountered = false;
	flags = 0;
	while (list)
	{
		redir = list->content;
		if (redir->is_ambiguous)
		{
			prefixed_error("ambiguous redirect\n");
			return (ERROR);
		}
		if (redir->direction == DIRECTION_IN && !in_encountered)
		{
			in_encountered = true;
			flags |= (O_RDONLY);
		}
		else if (redir->direction == DIRECTION_OUT)
			flags |= (O_CREAT | O_TRUNC | O_WRONLY);
		else if (redir->direction == DIRECTION_APPEND)
			flags |= (O_CREAT | O_APPEND | O_WRONLY);
		else if (redir->direction == DIRECTION_HEREDOC)
		{
			in_encountered = true;
			flags |= (O_RDONLY);
		}
		// TODO: Should still print "no such file" when a second input file isn't found
		open_fd = open(redir->file_path, flags, 0644);
		if (open_fd < 0)
			return (prefixed_perror(redir->file_path));
		if (redir->direction == DIRECTION_IN || redir->direction == DIRECTION_HEREDOC)
			cmd->input_fd = open_fd;
		if (redir->direction == DIRECTION_OUT || redir->direction == DIRECTION_APPEND)
			cmd->output_fd = open_fd;
		// TODO: Handle DIRECTION_HEREDOC
		list = list->next;
	}
	return (OK);
}

static void	dup2_cmd(t_cmd *cmd)
{
	// TODO: Protection necessary?

	dup2(cmd->input_fd, STDIN_FILENO);
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);

	dup2(cmd->output_fd, STDOUT_FILENO);
	if (cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
}

static t_status	execute_command(t_cmd *cmd, t_shell *lambda)
{
	char	**env_array;

	if (redirections(cmd->redirections, cmd) == ERROR)
	{
		// TODO: ??
		status = 1;
		return (ERROR);
	}

	// TODO: Try to find a way to not call this env_to_strings() every time
	env_array = env_to_strings(lambda->env);

	dup2_cmd(cmd);

	if (execve(cmd->path, cmd->args, env_array) == -1)
	{
		status = 127;
		return (prefixed_perror(cmd->path));
	}

	return (OK);
}

static t_status	execute_builtin(t_cmd *cmd, t_shell *lambda)
{
	if (redirections(cmd->redirections, cmd) == ERROR)
	{
		// TODO: ??
		status = 1;
		return (ERROR);
	}

	dup2_cmd(cmd);

	// TODO: Maybe if-statement check whether path or args or args[0] or args[1] is NULL?
	if (ft_streq(cmd->path, "cd"))
		status = cd(cmd, lambda);
	else if (ft_streq(cmd->path, "echo"))
		status = echo(cmd);
	else if (ft_streq(cmd->path, "env"))
		status = env(lambda);
	else if (ft_streq(cmd->path, "exit"))
		bltin_exit(cmd);
	else if (ft_streq(cmd->path, "export"))
		status = export(cmd, lambda);
	else if (ft_streq(cmd->path, "pwd"))
		status = pwd(lambda);
	else if (ft_streq(cmd->path, "unset"))
		status = unset(cmd, lambda);
	else if (!ft_streq(cmd->path, ""))
	{
		status = 127;
		prefixed_error(cmd->path);
		if (env_get_val(lambda->env, "PATH"))
			print_error(": command not found\n");
		else
			print_error(": No such file or directory\n");
		return (ERROR);
	}

	return (OK);
}

static int	get_wait_status(int stat_loc)
{
	// TODO: Add unit test for this one
	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	else if (WIFSIGNALED(stat_loc))
		return (WTERMSIG(stat_loc));
	// TODO: Probably also need to add this? Check by adding a unit test
	// else if (WIFSTOPPED(stat_loc))
	// 	return (WIFSTOPPED(stat_loc));
	return (0); // TODO: Is this wanted?
}

static t_status	execute_simple_command(t_cmd *cmd, t_shell *lambda)
{
	pid_t	pid;
	int		stat_loc;

	if (ft_strchr(cmd->path, '/'))
	{
		pid = fork();
		if (pid == FORK_FAILURE)
			return (prefixed_perror("execute_simple_command()"));
		if (pid == FORK_CHILD)
		{
			signal_handler_child_set();
			if (execute_command(cmd, lambda) == ERROR)
			{
				// TODO: Should anything be freed before this is called?
				exit(status);
			}
		}
		disable_signals();
		waitpid(pid, &stat_loc, 0);
		status = get_wait_status(stat_loc);
		signal_handler_set();
	}
	else
	{
		if (execute_builtin(cmd, lambda) == ERROR)
		{
			// TODO: Can this be moved to the end of execute_builtin()?
			dup2(lambda->stdin_fd, STDIN_FILENO);
			dup2(lambda->stdout_fd, STDOUT_FILENO);
			return (ERROR);
		}

		// TODO: Can this be moved to the end of execute_builtin()?
		// TODO: Should these both *always* happen?
		dup2(lambda->stdin_fd, STDIN_FILENO);
		dup2(lambda->stdout_fd, STDOUT_FILENO);
	}
	return (OK);
}

static t_status	execute_child(int input_fd, t_list *cmds, t_shell *lambda, int tube[2])
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
		if (execute_command(cmd, lambda) == ERROR)
		{
			// TODO: ??
		}
	}
	else
	{
		if (execute_builtin(cmd, lambda) == ERROR)
		{
			// TODO: ??
		}
	}
	exit(status); // TODO: Should anything be freed before this is called?
	return (OK);
}

static t_status	execute_complex_command(int input_fd, t_list *cmds, t_shell *lambda)
{
	int		tube[2];
	pid_t	pid;
	int		stat_loc;

	if (cmds->next && pipe(tube) == -1)
		return (prefixed_perror("execute_complex_command()"));
	pid = fork();
	if (pid == FORK_FAILURE)
		return (prefixed_perror("fork"));
	if (pid == FORK_CHILD)
	{
		signal_handler_child_set();
		if (execute_child(input_fd, cmds, lambda, tube) == ERROR)
		{
			// TODO: ??
		}
	}
	disable_signals();
	if (cmds->next)
		close(tube[WRITE]);
	if (input_fd != -1)
		close(input_fd); // TODO: Right now only the parent is closing the read end!!
	if (cmds->next && execute_complex_command(tube[READ], cmds->next, lambda) != OK)
	{
		if (errno != EAGAIN)
			return (prefixed_perror("execute_complex_command()"));
		return (ERROR);
	}
	waitpid(pid, &stat_loc, 0);
	if (!cmds->next)
		status = get_wait_status(stat_loc);
	return (OK);
}

t_status	execute(t_shell *lambda)
{
	if (lambda->cmds->next)
		return (execute_complex_command(-1, lambda->cmds, lambda));
	return (execute_simple_command(lambda->cmds->content, lambda));
}
