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

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdbool.h>
# include "../libft/libft.h"

// NOTE:
// Contains all data relevant to the operation of the shell.
typedef struct s_shell
{
	bool		interactive;
	t_list		*env;
	char		*line;
	char		**lines;
	char		*cwd;
	int			status;
	bool		stdin_is_tty;
	bool		exit;
	int			stdin_fd;
	int			stdout_fd;
}	t_shell;

typedef enum e_direction
{
	DIRECTION_HEREDOC,
	DIRECTION_APPEND,
	DIRECTION_IN,
	DIRECTION_OUT,
}	t_direction;

typedef struct s_redirect {
	char		*file_path;
	t_direction	direction;
	bool		is_ambiguous;
}	t_redirect;

typedef struct s_cmd
{
	int		i_fd;
	int		o_fd;
	t_list	*args;
	char	*path;
	t_list	*redirections;
}	t_cmd;

typedef struct s_env_element
{
	char	*key;
	char	*val;
}	t_env_element;

typedef enum s_token_type
{
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	REDIRECTION, // TODO: Might need to split into REDIRECTION_IN and _OUT
	PIPE,
	WHITESPACE,
	UNQUOTED,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
}	t_token;

typedef enum s_expansion_state
{
	EXPANSION_STATE_NORMAL,
	EXPANSION_STATE_VARIABLE,
	EXPANSION_STATE_STATUS,
	EXPANSION_STATE_INVALID_VARIABLE,
}	t_expansion_state;

#endif
