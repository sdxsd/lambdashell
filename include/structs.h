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

#ifndef STRUCTS_H
# define STRUCTS_H
# include "../libft/libft.h"

typedef struct s_env
{
	char	*key;
	char	*val;
	int		idx;
	void	*next;
}	t_env;

typedef struct s_ms
{
	char	*line;
	t_env	**env;
	char	**lines;
}	t_ms;

typedef enum e_token_type
{
	tkn_str,
	tkn_bltin,
	tkn_cmd,
	tkn_read,
	tkn_write,
	tkn_pipe,
	tkn_heredoc,
	tkn_append
}	t_token_type;

/*
 * NOTE:
 *                     +-----+
 *    /example/file -> | cmd | -> stdout | /other/file
 *                     +-----+
 * ALLOCATOR   : cmd_constructor()
 * DEALLOCATOR : cmd_deallocator()
*/

typedef struct s_cmd
{
	int		ret;
	int		i_fd;
	int		o_fd;
	char	**args;
	char	**env;
	char	*path;
}	t_cmd;

// NOTE:
//    EXECUTION LIST
// +------------------+
// | element[command] |
// +------------------+
//   | void *next
//   ---> +----------------------+
//        | element[redirection] |
//        +----------------------+
//        | void *next
//        --------> +---------------+
//                  | element[file] |
//                  +---------------+

// (int type) -> specifies the type of the element
//               i.e. command
//                    pipe
//                    builtin
//                    file
//                    redirection
// (void *value) -> structure of the element
//                  i.e. t_cmd
// (void *next)  -> next token element in the list.

// ALLOCATOR   : execution_list_generator();
// DEALLOCATOR : execution_list_deallocator();

typedef struct s_exec_element
{
	int		type;
	char	*line;
	void	*value;
	void	*next;
}	t_exec_element;

#endif
