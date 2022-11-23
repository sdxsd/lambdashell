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
#include <stdlib.h>
#include <unistd.h>

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

/* NOTE: exit calls are temporary until proper error handling is implemented. */
/* Utility function for combining program name and the paths.  */
static char	*combine_path(char *dir, char *prog_n)
{
	char	*abs_path;
	char	*dir_slash;

	dir_slash = ft_strjoin(dir, "/");
	if (!dir_slash)
		exit(1);
	abs_path = ft_strjoin(dir_slash, prog_n);
	if (!abs_path)
		exit(1);
	ft_free(&dir_slash);
	return (abs_path);
}

/* Takes program name (prog_n), and environment strings (env) and returns */
/* the absolute path to the program. */
char	*get_path(char *prog_n, t_vector *env)
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
	while (exec_direcs[iter])
	{
		abs_path = combine_path(exec_direcs[iter], prog_n);
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
