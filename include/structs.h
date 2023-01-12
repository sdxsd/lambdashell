/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
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

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include "enums.h"
# include "../libft/libft.h"

typedef struct t_lambda
{
	bool		interactive;
	t_list		*tokens;
	t_list		*env;
	t_list		*cmds;
	char		*line;
	char		*cwd;
	bool		stdin_is_tty;
	int			stdin_fd;
	int			stdout_fd;
}	t_lambda;

typedef struct s_redirect {
	char		*filepath;
	t_direction	direction;
	bool		is_ambiguous;
}	t_redirect;

typedef struct s_cmd
{
	int		input_fd;
	int		output_fd;
	char	**args;
	char	*path;
	t_list	*redirections;
}	t_cmd;

typedef struct s_env_element
{
	char	*key;
	char	*val;
}	t_env_element;

typedef struct s_token
{
	bool			was_single_quoted;
	t_token_type	type;
	char			*content;
	bool			is_ambiguous;
}	t_token;

typedef struct s_ambiguous_state
{
	bool	seen_content;
	bool	seen_word;
	bool	seen_env_space;
}	t_ambiguous_state;

typedef struct s_expand_state
{
	t_expansion_state	state;
	char				*substr_start;
	char				*expanded_string;
}	t_expand_state;

#endif
