/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
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

#ifndef MINISHELL_H
# define MINISHELL_H

/* HEADERS */
# include "structs.h"
# include "prototypes.h"
# include "splash.h"

/* LIBRARIES */
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* DEFINES */
# define READ 0
# define WRITE 1
# define TRUE 1
# define FALSE 0
# define FAILURE 1
# define SUCCESS 0
# define FORK_FAILURE -1
# define FORK_CHILD 0
# define FORK_PARENT 1
# define OUTPUT 1
# define INPUT 0

# define CLEAR "\033[0;0m"
# define RED "\033[0;31m"
# define GREEN "\033[1;32m"
# define BLUE "\033[1;34m"

/* GLOBAL VARIABLE */
/* int		global_sig; */

#endif
