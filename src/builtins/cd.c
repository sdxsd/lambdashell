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
#include <unistd.h>
#include <stdlib.h>

void	cd(t_cmd *cmd)
{
	// char	*line_count_str;
	// size_t	len;
	// char	*msg;

	// TODO: Add explicit "== -1" or DEFINE of -1
	if (chdir(cmd->args[1]))
		msg_err("cd", FAILURE);
	// {
	// 	line_count_str = ft_itoa(cmd->line_number);
	// 	if (!line_count_str)
	// 	{
	// 		// TODO: ?
	// 	}
	// 	// TODO: Is `cmd->args[1]` guaranteed to be non-NULL?
	// 	len = ft_strlen("line ") + ft_strlen(line_count_str) + ft_strlen(": cd: ") + ft_strlen(cmd->args[1]);
	// 	ft_free(&line_count_str);
	// 	msg = ft_calloc(len + 1, sizeof(char));
	// 	if (!msg)
	// 	{
	// 		// TODO: ?
	// 	}
	// 	ft_strlcat(msg, "line ", len + 1);
	// 	ft_strlcat(msg, line_count_str, len + 1);
	// 	ft_free(&line_count_str);
	// 	ft_strlcat(msg, ": cd: ", len + 1);
	// 	ft_strlcat(msg, cmd->args[1], len + 1);
	// 	msg_err(msg, FAILURE);
	// 	ft_free(&msg);
	// }
}
