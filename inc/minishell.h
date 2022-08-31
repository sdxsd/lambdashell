/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 22:28:26 by mikuiper      ########   odam.nl         */
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
int		global_sig;


typedef struct s_cmd
{
	int			fd_input;
	int			fd_output;
	int			fd_pipe[2];
	char		**cmd_split;
	char		*path;
}				t_cmd;

typedef struct	s_env
{
	char	*key;
	char	*val;
	int		idx;
	void	*next;
}				t_env;

typedef struct s_ms
{
	//char	**env;
	char	*input_line;
	t_cmd	*cmd;
	int		env_len;
	t_env	**env;
}			t_ms;

// PROTOTYPES
// INIT.C
int		init_start(void);
int		init_env(t_ms *ms, char **envp);
int		init_ms(t_ms *ms);

// ENV_TOOLS.C
int		add_env_idx(t_env **env);
int		env_len(t_env **env);
int		add_env_entry(t_ms *ms, t_env *new_node);
int		env_cloner(t_ms *ms, char *line);
int		get_env_key_pos(t_env **env, char *key);
char	*get_env_val(t_env **env, char *key);
int		env_edit_val(t_env **env, char *key, char *new_val);
// void	env_del_key(t_ms *ms, char *key);

// TOOLS.C
int		msg_err(char *s, int ret);

// INPUT.C
void	show_prompt(t_ms *ms);
int 	check_quotations(char *line);
int		check_first_char(char *line);
int		last_char(char *line);
int 	check_last_char(char *line, char *charset);
int		check_line_formatting(char *line, char *charset);
int		parse_input(t_ms *ms, char *line);

// PROMPT.C
void	show_prompt(t_ms *ms);

// CLEAN.C
int		clean_dp(char **dp);

// BUILTINS.C
int		ms_pwd(void);

// CMD.C

// DEBUG.C
int		dbg_print_env(t_ms *ms);
int		dbg_print_env_idx(t_ms *ms);
int		dbg_print_env_keys(t_ms *ms);

#endif