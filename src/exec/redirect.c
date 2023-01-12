/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
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
#include <fcntl.h>

int	get_flags(int dir)
{
	if (dir == DIRECTION_IN || dir == DIRECTION_HEREDOC)
		return (O_RDONLY);
	if (dir == DIRECTION_OUT)
		return (O_CREAT | O_TRUNC | O_WRONLY);
	if (dir == DIRECTION_APPEND)
		return (O_CREAT | O_APPEND | O_WRONLY);
	return (-1);
}

t_status	redirections(t_list *list, t_cmd *cmd)
{
	t_redirect	*redir;
	int			flags;
	int			open_fd;

	flags = 0;
	while (list)
	{
		redir = list->content;
		if (redir->is_ambiguous)
			return (prefixed_error("ambiguous redirect\n"));
		flags = get_flags(redir->direction);
		open_fd = open(redir->filepath, flags, 0644);
		if (open_fd < 0)
			return (prefixed_perror(redir->filepath));
		if (redir->direction == DIRECTION_IN || \
			redir->direction == DIRECTION_HEREDOC)
			cmd->input_fd = open_fd;
		if (redir->direction == DIRECTION_OUT || \
			redir->direction == DIRECTION_APPEND)
			cmd->output_fd = open_fd;
		list = list->next;
	}
	return (OK);
}
