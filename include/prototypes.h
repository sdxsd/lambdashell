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

/* ENVIRONMENT */
t_vector		*init_env(char **env);
char			**env_to_strings(t_vector *env);
char			*env_get_val(t_vector *env, char *key);
void			dealloc_env_element(void *ptr);
int				expand_env_variables(t_list *tokens, t_vector *env);

/* ERROR MESSAGES */
int				msg_err(char *s, int ret);
void			*null_msg_err(char *s);

/* TOKENISATION */
t_token			*get_token(t_token_type type, char *content);
t_token_type	subtokenize_single_quote(char **line_ptr);
t_token_type	subtokenize_double_quote(char **line_ptr);
t_token_type	subtokenize_redirection(char **line_ptr);
t_token_type	subtokenize_pipe(char **line_ptr);
t_token_type	subtokenize_whitespace(char **line_ptr);
t_token_type	subtokenize_unquoted(char **line_ptr);
t_list			*tokenize(char *line);

/* EXECUTION */
// int				execute_command(t_cmd *cmd);
// int				executor(int i_fd, t_exec_element *curr, t_shell *lambda);
// void			dealloc_exec_list(t_exec_element *head);

/* EXEC LIST */
// t_exec_element	*new_exec_element(void);
// void			free_exec_list(t_exec_element *head);

/* PARSE */
bool			is_ambiguous_redirect(t_list *tokens);
t_list			*parse(t_list *tokens);
void			skip_whitespace_tokens(t_list **tokens);

/* CMD STRUCT */
// t_cmd			*cmd_constructor(char *prog_n, t_vector *env);
// void			cmd_deallocator(t_cmd *cmd);

/* PATH */
char			*get_path(char *prog_n, t_vector *env);
int				free_ptr_array(char *ptr[]);

/* DEALLOC */
void			dealloc_ptr_array(void **data);
void			dealloc_lambda(t_shell *lambda);

/* DEBUG */
void			dbg_print_lines(char **lines);
void			dbg_print_env(t_vector *head);
void			dbg_print_cmd(t_cmd	*cmd);
void			dbg_test_env(t_vector *env);
void			dbg_print_tokens(t_list *tokens);
void			dbg_print_commands(t_list *cmds);

#endif
