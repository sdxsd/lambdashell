/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   appending.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/22 15:47:42 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/22 15:47:42 by sbos          ########   odam.nl         */
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

static char	*get_appended(char *content, t_expansion_state state,
				char *substr_start, t_lambda *lambda)
{
	char	*appended;
	char	*env_key;
	char	*env_val;

	if (state == EXPANSION_STATE_NORMAL)
		appended = ft_substr(substr_start, 0, content - substr_start);
	else if (state == EXPANSION_STATE_VARIABLE)
	{
		env_key = ft_substr(substr_start, 1, content - substr_start - 1);
		if (!env_key)
			return (NULL);
		env_val = env_get_val(lambda->env, env_key);
		ft_free(&env_key);
		if (env_val)
			appended = ft_strdup(env_val);
		else
			appended = ft_strdup("");
	}
	else if (state == EXPANSION_STATE_STATUS)
		appended = ft_itoa(g_status);
	else
		appended = ft_strdup("");
	return (appended);
}

char	*strjoin_appended(char *content, t_expand_state *state,
			t_lambda *lambda)
{
	char	*appended;

	appended = get_appended(content, state->state, state->substr_start, lambda);
	if (!appended)
	{
		ft_free(&state->expanded_string);
		return (perror_malloc_null());
	}
	return (ft_strjoin_and_free_left_right(state->expanded_string, &appended));
}

t_status	append(char *content, t_expand_state *state, t_lambda *lambda)
{
	char	*appended;

	appended = get_appended(content, state->state, state->substr_start, lambda);
	if (!appended)
	{
		ft_free(&state->expanded_string);
		return (perror_malloc());
	}
	state->substr_start = content;
	state->expanded_string = ft_strjoin_and_free_left_right(
			state->expanded_string, &appended);
	if (!state->expanded_string)
		return (perror_malloc());
	state->state = EXPANSION_STATE_NORMAL;
	return (OK);
}
