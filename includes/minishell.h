/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/12 15:02:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// LIBRARIES
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// GLOBAL VARIABLE
//int		global_sig;

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

typedef enum	e_token_type
{
	tkn_str,
	tkn_read,
	tkn_write,
	tkn_pipe,
	tkn_heredoc,
	tkn_append
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*val;
}				t_token;

/*
 * NOTE:
 *                     +-----+
 *    /example/file -> | cmd | -> stdout | /other/file
 *                     +-----+
*/

typedef struct	s_cmd
{
	int		i_fd;
	int		o_fd;
	char	**args;
	char	**env;
	char	*path;
}				t_cmd;

/*
 * NOTE:
 *      PIPE BLOCK
 * +--------------------+
 * | cmd_one -> cmd_two | -> stdout
 * +--------------------+
 * +--------------------+    +------------------+
 * | cmd_one -> cmd_two | -> | OTHER PIPE BLOCK |
 * +--------------------+    +------------------+
 * +--------------------+
 * | cmd_one -> cmd_two | -> /something/example.file
 * +--------------------+
 */

typedef struct	s_pipe_blck
{
	int		i_fd;
	int		o_fd;
	int		pipe[2];
	t_cmd	*cmd_one;
	t_cmd	*cmd_two;
}				t_pipe_blck;

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
void	msg_err(char *s, int ret);

// INPUT.C
int		check_first_char(char *line);
int		check_line_formatting(char *line, char *charset);
int		last_char(char *line);
int 	check_last_char(char *line, char *charset);
int 	check_quotations(char *line);
int		line_parser(t_ms *ms);
void	prompt_start(t_ms *ms);

// CLEAN.C
int		clean_tokenlist(t_list **tokenlist);
int		clean_env(t_env **env);

// BUILTINS.C
int		ms_pwd(void);

// TOKENIZER.C
int		token_make_and_add(char *token, t_list **tokenlist);
int		line_tokenizer(char *line, t_list **tokenlist);
void	token_add_types(void *token);
int		check_token_formatting(t_list **tokenlist);

// COMMANDS.C

// DEBUG.C
int		dbg_print_env(t_ms *ms);
int		dbg_print_env_idx(t_ms *ms);
int		dbg_print_env_keys(t_ms *ms);
int		dbg_print_tokens_val(t_list **tokenlist);
int		dbg_print_tokens(t_list **tokenlist);

#endif
