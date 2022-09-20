/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prototypes.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 13:35:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/20 21:46:53 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "structs.h"

/* SPLASH.C */
void	splash();
void	clear_screen(void);

/* INIT.C */
int		init_env_struct(t_ms *ms, char **envp);
int		init_ms_struct(t_ms *ms);
int		init_start(void);

/* MAIN.C */
int		prompt(t_ms *ms);

/* EXPANDER.C */
char	*line_expander(char *line, t_env **env);
char	*line_insert_var(char *line, int pos, t_env **env);
int		line_dollar_presence(char *line);

/* ENV */
/* ENV_ADD_VAR.C */
t_env	*env_create_var(char *key, char *val);
int		env_add_var(t_ms *ms, t_env *node);

/* ENV_TOOLS.C */
int		env_len(t_env **env);
int		env_get_var_key_idx(t_env **env, char *key);
char	*env_get_val(t_env **env, char *key);
int		env_init_idx(t_env **env);
int		env_edit_var_val(t_env **env, char *key, char *new_val);

/* ENV_CLONE_ENV */
int	env_var_cloner(t_ms *ms, char *line);

/* ENV_DELETE_VAR */
int		free_env_var(t_env *node);
int		env_del_var_helper(t_env **head, char *key);
int		env_del_var(t_env **env, char *key);

/* ERROR.C */
int		msg_err(char *s, int ret);

/* EXEC.C */
int		execute_command(t_cmd *cmd);

/* INPUT.C */
int		line_check_first_char(char *line);
int		line_check_syntax(char *line, char *charset);
int		line_get_last_char(char *line);
int 	line_check_last_char(char *line, char *charset);
int 	line_check_quotations(char *line);
int		line_parser(t_ms *ms);

/* CLEAN.C */
int		clean_tokenlist(t_list **tokenlist);
int		clean_env(t_env **env);

/* BUILTINS */
/* ENV.C */
void	builtin_env(t_ms *ms, int fd);
int		builtin_pwd(void);
void	builtin_unset(char **keys, t_ms *ms);

/* tokens_populate_tokenlist.C */
int		tokens_check_syntax(t_list *tokenlist);
void	tokens_add_types(t_list *tokenlist);

/* MAKE_TOKENLIST */
int		tokens_make_and_add(char *token, t_list **tokens);
//int		tokens_populate_tokenlist(char *line, t_list **tokens);
int	tokens_populate_tokenlist(char **lines, t_list **tokens);
int		tokens_get_pipe_blk_len(t_list *tokenlist);
t_list	*make_token_blks_list(t_list **tokenlist);
char	**get_tokens_array(t_list *tokenlist);
int		tokens_make_and_add_token_blk(t_list **pipe_blk_list, char **token_array);

/* PIPE_blk.C */
t_cmd		*cmd_constructor(char *prog_n, t_env **env);
void		cmd_deallocator(t_cmd *cmd);
t_pipe_blk	*pipe_blk_alloc(t_cmd *cmd_one, t_cmd *cmd_two, int i, int o);
void		pipe_blk_dealloc(t_pipe_blk *pipe_blk);

/* PATH.C */
char	*get_path(char *prog_n, t_env **env);
int		free_ptr_array(char *ptr[]);

/* DEBUG_ENV.C */
int		debug_print_env(t_ms *ms);
int		debug_print_env_idx(t_ms *ms);
int		debug_print_env_keys(t_ms *ms);

/* DEBUG_TOKENLIST.C */
int		debug_print_tokens_val(t_list **tokenlist);
int		debug_print_tokens(t_list **tokenlist);
int		debug_print_token_blks_list(t_list *token_blks_list);

/* MISC */
/* CHECK_FD.C */
int		check_fd(void);

/* COLORS.C */
void	color_red();
void	color_orange();
void	color_green();
void	color_reset();

#endif
