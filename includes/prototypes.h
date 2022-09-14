/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prototypes.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 13:35:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/14 13:41:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/* SPLASH.C */
void	splash();

/* INIT.C */
int		init_env(t_ms *ms, char **envp);
int		init_ms(t_ms *ms);
int		init_start(void);

/* PROMPT.C */
int		prompt(t_ms *ms);

/* EXPANDER.C */
char	*line_expander(char *line, t_env **env);
char	*line_expander_helper(char *line, int pos, t_env **env);

/* ENV_TOOLS.C */
char	*get_env_val(t_env **env, char *key);
int		env_del_entry(t_env **head, char *key);
int		env_edit_val(t_env **env, char *key, char *new_val);
int		env_entry_cloner(t_ms *ms, char *line);
int		env_len(t_env **env);
int		free_env_node(t_env *node);
int		get_env_key_idx(t_env **env, char *key);
int		init_env_idx(t_env **env);

/* ERROR.C */
int	msg_err(char *s, int ret);

/* EXEC.C */
int	execute_command(t_cmd *cmd);

/* INPUT.C */
int		check_first_char(char *line);
int		check_line_formatting(char *line, char *charset);
int		last_char(char *line);
int		parse_input(t_ms *ms, char *line);
int 	check_last_char(char *line, char *charset);
int 	check_quotations(char *line);
void	line_parser(t_ms *ms);
void	prompt_start(t_ms *ms);

/* CLEAN.C */
int		clean_tokenlist(t_list **tokenlist);
int		clean_env(t_env **env);

/* BUILTINS.C */
int		ms_pwd(void);

/* TOKENIZER.C */
int		token_make_and_add(char *token, t_list **tokens);
int		tokenizer(char *line, t_list **tokens);
void	token_add_types(void *in);
int		token_checker(t_list *tokenlist);

/* PIPE_BLOCK.C */
t_cmd		*cmd_constructor(char *prog_n, t_env **env);
void		cmd_deallocator(t_cmd *cmd);
t_pipe_blk	*pipe_blk_alloc(t_cmd *cmd_one, t_cmd *cmd_two, int i, int o);
void		pipe_blk_dealloc(t_pipe_blk *pipe_blk);

/* PATH.C */
char	*get_path(char *prog_n, t_env **env);
int		free_ptr_array(char *ptr[]);

/* DEBUG.C */
int		dbg_print_env(t_ms *ms);
int		dbg_print_env_idx(t_ms *ms);
int		dbg_print_env_keys(t_ms *ms);
int		dbg_print_tokens_val(t_list **tokenlist);
int		dbg_print_tokens(t_list **tokenlist);

/* COLORS.C */
void	color_red();
void	color_orange();
void	color_green();
void	color_reset();

#endif
