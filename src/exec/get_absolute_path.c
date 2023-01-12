/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_absolute_path.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 17:10:32 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/12 17:10:32 by sbos          ########   odam.nl         */
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

static char	*path_join(char *dir, char *name)
{
	return (ft_strjoin_array((char *[]){dir, "/", name, NULL}));
}

static char	*get_absolute_path_from_name(char *name, char **path_parts)
{
	size_t	path_part_index;
	char	*absolute_path;

	path_part_index = 0;
	while (path_parts[path_part_index])
	{
		absolute_path = path_join(path_parts[path_part_index], name);
		if (!absolute_path)
			return (perror_malloc_null());
		if (access(absolute_path, F_OK | X_OK) == FILE_EXISTS)
			return (absolute_path);
		ft_free(&absolute_path);
		path_part_index++;
	}
	return (name);
}

char	*get_absolute_path(char *name, t_list *env)
{
	char	*path;
	char	**path_parts;
	char	*absolute_path;

	path = env_get_val(env, "PATH");
	if (!path || ft_streq(name, ""))
		return (name);
	path_parts = ft_split(path, ':');
	if (!path_parts)
		return (perror_malloc_null());
	absolute_path = get_absolute_path_from_name(name, path_parts);
	dealloc_ptr_array(&path_parts);
	return (absolute_path);
}
