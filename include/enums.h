/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enums.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/30 21:10:03 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/30 21:10:03 by sbos          ########   odam.nl         */
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

#ifndef ENUMS_H
# define ENUMS_H

typedef enum s_status
{
	OK,
	ERROR,
}	t_status;

typedef enum e_direction
{
	DIRECTION_HEREDOC,
	DIRECTION_APPEND,
	DIRECTION_IN,
	DIRECTION_OUT,
}	t_direction;

typedef enum s_expansion_state
{
	EXPANSION_STATE_NORMAL,
	EXPANSION_STATE_VARIABLE,
	EXPANSION_STATE_STATUS,
	EXPANSION_STATE_INVALID_VARIABLE,
}	t_expansion_state;

typedef enum s_token_type
{
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	REDIRECTION,
	HEREDOC,
	PIPE,
	WHITESPACE,
	UNQUOTED,
	UNMATCHED_QUOTE,
}	t_token_type;

#endif
