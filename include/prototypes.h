/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prototypes.h                                       :+:    :+:            */
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

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "structs.h"

/* ALLOC */
t_env_element	*alloc_env_element(void);

/* BUILTINS */
int				cd(t_cmd *cmd, t_shell *lambda);
int				env(t_shell *lambda);
void			bltin_exit(t_cmd *cmd, t_shell *lambda);
int				export(t_cmd *cmd, t_shell *lambda);
int				pwd(t_shell *lambda);
int				unset(t_cmd *cmd, t_shell *lambda);

/* COSMETIC */
char			*get_readline_str(t_shell *lambda);

/* DEALLOC */
int				dealloc_cmd(void *cmd_ptr);
int				dealloc_env_element(void *env_element_ptr);
int				dealloc_token(void *token_ptr);
int				dealloc_lambda(t_shell *lambda);
void			dealloc_ptr_array(void *ptr_array_ptr);
int				dealloc_redirection(void *redirect_ptr);

/* DEBUG */
void			dbg_print_tokens(t_list *tokens);
void			dbg_print_commands(t_list *cmds);

/* ENVIRONMENT */
int				add_env_element(char *env_line, t_list **env);
int				init_env(char **env, t_list **lambda_env);
char			**env_to_strings(t_list *env);
char			*env_get_val(t_list *env, char *key);
int				expand_variables(t_list *tokens, t_shell *lambda);

/* ERROR MESSAGES */
int				msg_err(char *s, int ret);
void			*null_msg_err(char *s);

/* EXECUTION */
int				execute(t_list *cmds, t_shell *lambda);
char			*get_absolute_path_from_env(char *name, t_list *env);

/* PARSE */
bool			is_ambiguous_redirect(t_list *tokens);
bool			is_text_token(t_token *token);
t_list			*parse(t_list *tokens, t_list *env);
void			skip_whitespace_tokens(t_list **tokens);

/* TOKENISATION */
t_token			*get_token(t_token_type type, char *content);
t_token_type	subtokenize_single_quote(char **line_ptr);
t_token_type	subtokenize_double_quote(char **line_ptr);
t_token_type	subtokenize_heredoc(char **line_ptr);
t_token_type	subtokenize_append(char **line_ptr);
t_token_type	subtokenize_redirection(char **line_ptr);
t_token_type	subtokenize_pipe(char **line_ptr);
t_token_type	subtokenize_whitespace(char **line_ptr);
t_token_type	subtokenize_unquoted(char **line_ptr);
t_list			*tokenize(char *line);

/* UPDATE_CWD */
void			update_cwd(t_shell *lambda);

/* EXECUTION */
int				executor(int i_fd, t_list *cmds, t_shell *lambda);

/* PARSE */
bool			is_ambiguous_redirect(t_list *tokens);
bool			is_text_token(t_token *token);
t_list			*parse(t_list *tokens, t_list *env);
void			skip_whitespace_tokens(t_list **tokens);

/* PATH */
char			*get_absolute_path_from_env(char *name, t_list *env);

/* DEALLOC */
void			dealloc_ptr_array(void *ptr_array_ptr);
int				dealloc_lambda(t_shell *lambda);
void			dealloc_cmds(t_list *cmds);
int				dealloc_cmd(void *cmd_ptr);
void			dealloc_redirections(t_list *redir);

/* DEBUG */
void			dbg_print_tokens(t_list *tokens);
void			dbg_print_commands(t_list *cmds);
void			dbg_print_lines(char **lines);

#endif
