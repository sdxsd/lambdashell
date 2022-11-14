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

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "structs.h"

/* COSMETIC */
void			clear(void);
void			red(void);
void			green(void);
void			blue(void);
void			ps1(t_shell	*lambda);

/* BUILTINS */
char			*ret_cwd(void);
int				pwd(void);
void			cd(t_cmd *cmd);
t_cmd			*bltin_constructor(char	*line, t_vector *env);

/* SHELL */
int				prompt(t_shell *ms);

/* ENVIRONMENT */
t_vector		*init_env(char **env);
char			**env_to_strings(t_vector *env);
t_env_element	*env_get_val(t_vector *env, char *key);

/* ERROR MESSAGES */
int				msg_err(char *s, int ret);
void			*null_msg_err(char *s);

/* TOKENISATION */
t_exec_element	*tokenizer(t_shell *lambda);

/* EXECUTION */
int				execute_command(t_cmd *cmd);
int				executor(t_exec_element *head, t_vector *env, t_shell *lambda);
void			dealloc_exec_list(t_exec_element *head);

/* EXEC LIST */
t_exec_element	*exec_list_generator(t_exec_element *head, t_vector *env);
t_exec_element	*new_exec_element(void);
void			free_exec_list(t_exec_element *head);
int				count_elements(t_exec_element *head);

/* LINE PARSER */
int				parse_line(t_shell *lambda);

/* CMD STRUCT */
t_cmd			*cmd_constructor(char *prog_n, t_vector *env);
void			cmd_deallocator(t_cmd *cmd);

/* PATH */
char			*get_path(char *prog_n, t_vector *env);
int				free_ptr_array(char *ptr[]);

/* DEBUG */
void			dbg_print_exec_list(t_exec_element *head);
void			dbg_print_lines(char **lines);
void			dbg_print_env(t_vector *head);
void			dbg_print_cmd(t_cmd	*cmd);
void			dbg_test_env(t_vector *env);

/* DEALLOC */
void			dealloc_ptr_array(void *data[]);

#endif
