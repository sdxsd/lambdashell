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

void	dealloc_env_element(void *ptr)
{
	t_env_element	*env_element;

	env_element = ptr;
	free(env_element->key);
	free(env_element->val);
	free(env_element);
}

static int	to_assignment(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0' && str[count] != '=')
		count++;
	return (count);
}

static void	*init_env_failure(t_vector *env)
{
	return (free_vector(env, dealloc_env_element));
}

t_vector	*init_env(char **env)
{
	t_vector		*env_vector;
	t_env_element	*env_element;
	int				iter;

	iter = 0;
	while (env[iter])
		iter++;
	env_vector = alloc_vector(iter - 1);
	if (!env_vector)
		return (NULL);
	while (iter-- > 0)
	{
		env_element = malloc(sizeof(t_env_element));
		if (!env_element)
			return (init_env_failure(env_vector));
		env_element->key = ft_strndup(env[iter], to_assignment(env[iter]) + 1);
		if (!env_element->key)
			return (init_env_failure(env_vector));
		env_element->val = ft_strdup(env[iter] + to_assignment(env[iter]) + 1);
		if (!env_element->key)
			return (init_env_failure(env_vector));
		vec_assign_element(env_vector, iter, env_element);
	}
	return (env_vector);
}

t_env_element	*env_get_val(t_vector *env, char *key)
{
	int				iter;
	int				env_size;
	t_env_element	*env_element;

	if (!env || !key)
		return (NULL);
	iter = 0;
	env_size = vector_size(env);
	while (iter < env_size)
	{
		env_element = vec_get_element(env, iter)->data;
		if (ft_streq(env_element->key, val))
			return (env_element);
		iter++;
	}
	return (NULL);
}
