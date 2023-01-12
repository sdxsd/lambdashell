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
	- The freedom to improve the program, and release your improvements
	to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include "minishell.h"

static char	*path_join(char *dir, char *name)
{
	return (ft_strjoin_array((char *[]){dir, "/", name, NULL}));
}

static char	*get_absolute_path_from_name(char *name, char **exec_direcs)
{
	size_t	iter;
	char	*absolute_path;

	iter = 0;
	while (exec_direcs[iter])
	{
		absolute_path = path_join(exec_direcs[iter], name);
		if (!absolute_path)
			return (perror_malloc_null());
		if (access(absolute_path, F_OK | X_OK) == FILE_EXISTS)
			return (absolute_path);
		ft_free(&absolute_path);
		iter++;
	}
	return (name);
}

char	*get_absolute_path(char *name, t_list *env)
{
	char	*path;
	char	**exec_direcs;
	char	*absolute_path;

	path = env_get_val(env, "PATH");
	if (!path || ft_streq(name, ""))
		return (name);
	exec_direcs = ft_split(path, ':');
	if (!exec_direcs)
		return (perror_malloc_null());
	absolute_path = get_absolute_path_from_name(name, exec_direcs);
	dealloc_ptr_array(&exec_direcs);
	return (absolute_path);
}