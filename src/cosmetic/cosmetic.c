/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cosmetic.c                                         :+:    :+:            */
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

static char	*last_directory(char *line)
{
	char	*leaf_dir;
	size_t	character_index;

	leaf_dir = line;
	character_index = 0;
	while (character_index < ft_strlen(line))
	{
		if (line[character_index] == '/')
			leaf_dir = line + character_index + 1;
		character_index++;
	}
	return (leaf_dir);
}

// Prompt string one
char	*get_readline_str(t_lambda *lambda)
{
	char	*user;
	char	*leaf_dir;
	char	*readline_str;

	user = env_get_val(lambda->env, "USER");
	if (!user)
		user = "???";
	if (lambda->cwd)
		leaf_dir = last_directory(lambda->cwd);
	else
		leaf_dir = "???";
	readline_str = ft_strjoin_array((char *[]){"[", user, "] ", leaf_dir, " ", \
		PREFIX" :: ❯ ", NULL});
	return (readline_str);
}
