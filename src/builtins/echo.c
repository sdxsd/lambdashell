/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
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

size_t	process_args(t_cmd *cmd, bool *nl)
{
	size_t	iter;

	iter = 1;
	if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		while (cmd->args[1][iter] == 'n')
			iter++;
		if (iter == ft_strlen(cmd->args[1]))
		{
			iter = 2;
			*nl = FALSE;
		}
	}
	return (iter);
}

t_status	echo(t_cmd *cmd)
{
	size_t	iter;
	bool	nl;

	nl = TRUE;
	iter = process_args(cmd, &nl);
	while (cmd->args[iter] != NULL)
	{
		ft_putstr(cmd->args[iter]);
		if (!(cmd->args[iter + 1] == NULL))
			ft_putchar(' ');
		iter++;
	}
	if (nl == TRUE)
		ft_putstr("\n");
	return (0);
}
