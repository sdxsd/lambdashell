/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/10 23:23:30 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// LIBRARIES
# include "../libft/libft.h"
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// GLOBAL VARIABLE
//int		global_sig;


// typedef struct s_cmd
// {
// 	int			fd_input;
// 	int			fd_output;
// 	int			fd_pipe[2];
// 	char		**split;
// 	char		*path;
// }				t_cmd;

// typedef struct s_token
// {
// 	char			*value;
// 	struct s_token	*prev;
// 	struct s_token	*next;
// }					t_token;

typedef struct	s_env
{
	char	*key;
	char	*val;
	int		idx;
	void	*next;
}				t_env;

typedef struct s_ms
{
	char	*line;
	int		env_len;
	t_list	*tokens;
	t_env	**env;
}			t_ms;

typedef enum e_token_tag
{
	tkn_str,
	tkn_read,
	tkn_write,
	tkn_pipe,
	tkn_heredoc,
	tkn_append
}				t_token_tag;

typedef struct s_token
{
	t_token_tag	tag;
	char		*txt;
}				t_token;

// PROTOTYPES
// INIT.C
int		init_env(t_ms *ms, char **envp);
int		init_ms(t_ms *ms);
int		init_start(void);

// PROMPT.C
int		prompt(t_ms *ms);

// EXPANDER.C
char	*line_expander(char *line, t_env **env);
char	*line_expander_helper(char *line, int pos, t_env **env);

// ENV_TOOLS.C
char	*get_env_val(t_env **env, char *key);
int		env_del_entry(t_env **head, char *key);
int		env_edit_val(t_env **env, char *key, char *new_val);
int		env_entry_cloner(t_ms *ms, char *line);
int		env_len(t_env **env);
int		free_env_node(t_env *node);
int		get_env_key_idx(t_env **env, char *key);
int		init_env_idx(t_env **env);

// TOOLS.C
int		msg_err(char *s, int ret);

// INPUT.C
int		check_first_char(char *line);
int		check_line_formatting(char *line, char *charset);
int		last_char(char *line);
int		parse_input(t_ms *ms, char *line);
int 	check_last_char(char *line, char *charset);
int 	check_quotations(char *line);
void	line_parser(t_ms *ms);
void	prompt_start(t_ms *ms);

// CLEAN.C
int		clean_dp(char **dp);

// BUILTINS.C
int		ms_pwd(void);

// TOKENIZER.C
int		token_make_and_add(char *token, t_list **tokens);
int		tokenizer(char *line, t_list **tokens);
void	token_add_tags(void *in);

// COMMANDS.C

// DEBUG.C
int		dbg_print_env(t_ms *ms);
int		dbg_print_env_idx(t_ms *ms);
int		dbg_print_env_keys(t_ms *ms);
int		dbg_print_tokens_txt(t_list **tokenlist);
int		dbg_print_tokens(t_list **tokenlist);

#endif