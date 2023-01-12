/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
THIS FILE IS LICENSED UNDER THE GNU GPLv3
Copyright (C) 2022 Will Maguire and Sander Bos

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
	- The freedom to improve the program, and release your improvements
	to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include "minishell.h"

static size_t	get_first_arg_index_to_echo(t_cmd *cmd, bool *print_newline_ptr)
{
	size_t	character_index;
	size_t	arg_index;
	size_t	first_arg_index_to_echo;

	arg_index = 1;
	first_arg_index_to_echo = 1;
	while (cmd->args[arg_index] && cmd->args[arg_index][0] == '-')
	{
		character_index = 1;
		while (cmd->args[arg_index][character_index] == 'n')
			character_index++;
		if (character_index == ft_strlen(cmd->args[arg_index]))
		{
			first_arg_index_to_echo++;
			*print_newline_ptr = false;
		}
		arg_index++;
	}
	return (first_arg_index_to_echo);
}

t_status	echo(t_cmd *cmd)
{
	size_t	arg_index;
	bool	print_newline;

	print_newline = true;
	arg_index = get_first_arg_index_to_echo(cmd, &print_newline);
	while (cmd->args[arg_index])
	{
		ft_putstr(cmd->args[arg_index]);
		if (cmd->args[arg_index + 1])
			ft_putchar(' ');
		arg_index++;
	}
	if (print_newline)
		ft_putstr("\n");
	return (0);
}
