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
# include <stdbool.h>
# include "../libft/libft.h"

// NOTE:
// Contains all data relevant to the operation of the shell.
typedef struct s_shell
{
	bool		interactive;
	t_vector	*env;
	char		*line;
	char		**lines;
	bool		i_tty;
	bool		exit;
}	t_shell;

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

// ERR_GENERIC = unknown error type.
// ERR_PARSING = problem with input.
// ERR_NULLRET = function returned null
// ERR_ALLOCFU = allocation fucked up
// RET_SUCCESS = everything went fine.
typedef enum e_err
{
	ERR_GENERIC,
	ERR_PARSING,
	ERR_NULLRET,
	ERR_ALLOCFU,
	RET_SUCCESS,
}	t_err;

// NOTE:
// direc == TRUE then output.
// direc == FALSE then input.
// char *file points to name of file involved.
typedef struct s_redirec {
	char	*file;
	bool	direc;
} t_redirec;

// NOTE:
//                     +-----+
//    /example/file -> | cmd | -> stdout | /other/file
//                     +-----+
// ALLOCATOR   : cmd_constructor()
// DEALLOCATOR : cmd_deallocator()

typedef struct s_cmd
{
	int			ret;
	int			i_fd;
	int			o_fd;
	char		**args;
	char		**env;
	char		*path;
	t_redirec	*redir;
}	t_cmd;

typedef struct s_env_element
{
	char	*key;
	char	*val;
}	t_env_element;

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

// ALLOCATOR   : exec_list_generator();
// DEALLOCATOR : exec_list_deallocator();

typedef struct s_exec_element
{
	int						type;
	char					*line;
	void					*value;
	struct s_exec_element	*next;
}	t_exec_element;

#endif
