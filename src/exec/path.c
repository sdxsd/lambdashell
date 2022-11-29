/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
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

/* Returns number of elements freed */
/* Assumes list ends with null ptr */
int	free_ptr_array(char *ptr[])
{
	int	iter;

	iter = 0;
	while (ptr[iter])
	{
		ft_free(&ptr[iter]);
		iter++;
	}
	ft_free(&ptr);
	return (iter);
}

static char	*path_join(char *dir, char *name)
{
	return (ft_strjoin_array((char *[]){dir, "/", name, NULL}));
}

/* Takes program name (prog_n), and environment strings (env) and returns */
/* the absolute path to the program. */
char	*get_path_from_name(char *name, t_vector *env)
{
	static char	*path;
	char		*abs_path;
	char		**exec_direcs;
	int			iter;

	iter = 0;
	if (!path)
		path = env_get_val(env, "PATH");
	if (!path)
		return (NULL);
	exec_direcs = ft_split(path, ':');
	if (!exec_direcs)
		return (NULL);
	while (exec_direcs[iter])
	{
		abs_path = path_join(exec_direcs[iter], name);
		if (!abs_path)
		{
			free_ptr_array(exec_direcs);
			return (NULL);
		}
		if (!access(abs_path, F_OK)) // TODO: Probably needs more flags
		{
			free_ptr_array(exec_direcs);
			return (abs_path);
		}
		ft_free(&abs_path);
		iter++;
	}
	free_ptr_array(exec_direcs);
	return (NULL);
}
