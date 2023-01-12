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
t_token			*alloc_token(t_token_type type, char *content);
t_status		alloc_cmd(t_cmd **cmd_ptr);
t_redirect		*alloc_redirect(char *filepath, t_direction direction,
					bool is_ambiguous);

/* BUILTINS */
t_status		cd(t_cmd *cmd, t_shell *lambda);
t_status		env(t_shell *lambda);
void			bltin_exit(t_cmd *cmd);
t_status		export(t_cmd *cmd, t_shell *lambda);
t_status		pwd(t_shell *lambda);
t_status		unset(t_cmd *cmd, t_shell *lambda);
t_status		echo(t_cmd *cmd);

/* COSMETIC */
char			*get_readline_str(t_shell *lambda);

/* DEALLOC */
t_status		dealloc_cmd(void *cmd_ptr);
t_status		dealloc_env_element(void *env_element_ptr);
t_status		dealloc_token(void *token_ptr);
t_status		dealloc_ptr_array(void *ptr_array_ptr);
t_status		dealloc_redirect(void *redirect_ptr);
t_status		dealloc_lst(t_list **lst, t_status (*del)(void*));
t_status		dealloc_lambda(t_shell *lambda);
void			dealloc_and_exit(t_status status, t_shell *lambda);

/* DEBUG */
void			dbg_print_tokens(t_list *tokens);
void			dbg_print_commands(t_list *cmds);

/* ENV */
t_status		add_or_change_env_element(char *env_line, t_list **env_ptr);
t_status		init_env(char **env, t_list **lambda_env_ptr);
char			*env_get_val(t_list *env, char *key);
t_status		expand_variables(t_list **tokens_list, t_shell *lambda);
char			**env_to_strings(t_list *env);
bool			is_valid_name_chr(char chr);
bool			is_valid_name_first_chr(char chr);
bool			is_valid_identifier(char *name);
size_t			get_key_length(char *str);
t_status		add_env_element(char *key, char *val, t_list **env_ptr);

/* ERROR */
t_status		print_error(char *msg);
t_status		prefixed_error(char *msg);
t_status		prefixed_perror(char *msg);

t_status		perror_error(char *msg);
t_status		perror_malloc(void);
void			*perror_malloc_null(void);

/* EXEC */
t_status		execute(t_shell *lambda);
char			*get_absolute_path(char *name, t_list *env);
t_status		redirections(t_list *list, t_cmd *cmd);
t_status		execute_builtin(t_cmd *cmd, t_shell *lambda);
void			dup2_cmd(t_cmd *cmd);
int				get_wait_status(int stat_loc);
t_status		exec_complex_cmd(int i_fd, t_list *cmds, t_shell *lambda);
t_status		execute_command(t_cmd *cmd, t_shell *lambda);

/* HEREDOC */
t_status		expand_heredoc_tokens(t_token *delimiter, t_list *tokens,
					t_shell *lambda);
char			*heredoc(t_token *delimiter, t_shell *lambda);
void			cleanup_heredocs(t_list *cmds);
t_status		heredocs(t_list *tokens, t_shell *lambda);

/* NULL */
void			*null(t_status _);

/* PARSE */
t_status		add_arg(t_list **arg_list_ptr, t_list **tokens_ptr);
t_status		add_redirect(t_list **tokens_ptr, t_list **redirections_ptr);
char			**get_arg_string_array(t_list *arg_list);
t_list			*parse(t_list *tokens, t_list *env);

/* SIGNALS */
void			signal_handler_set(void);
void			signal_handler_child_set(void);
void			disable_signals(void);

/* STOP */
bool			running(void);
t_status		stop(void);
void			stop_void(void);

/* TOKENIZE */
t_status		check_token_syntax_errors(t_list *tokens);
bool			is_text_token(t_token *token);
void			mark_ambiguous_redirects(t_list *tokens);
void			skip_whitespace_tokens(t_list **tokens);
t_status		split_and_add_spaced_tokens(t_token *token, t_list *current);
t_token_type	subtokenize_single_quote(char **line_ptr);
t_token_type	subtokenize_double_quote(char **line_ptr);
t_token_type	subtokenize_heredoc(char **line_ptr);
t_token_type	subtokenize_append(char **line_ptr);
t_token_type	subtokenize_redirection(char **line_ptr);
t_token_type	subtokenize_pipe(char **line_ptr);
t_token_type	subtokenize_whitespace(char **line_ptr);
t_token_type	subtokenize_unquoted(char **line_ptr);

t_list			*tokenize(char *line);
t_status		whitespace_split_tokens(t_list **tokens_ptr);

/* UPDATE_CWD */
t_status		update_cwd(t_shell *lambda);

#endif
