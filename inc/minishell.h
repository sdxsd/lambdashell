/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/25 14:42:35 by mikuiper      ########   odam.nl         */
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
//char    **env_global;

typedef struct s_ms
{
	char	**env;
}			t_ms;

// PROTOTYPES
// init.c
int		init_ms(t_ms *ms);
int		init_env(t_ms *ms, char **envp);
int		duplicate_env(char **target, char **source);
int		env_write_entry(t_ms *ms, int pos, char *entry);
int		env_find_key(t_ms *ms, char *key);
int		env_add_entry(t_ms *ms, char *key, char *value);
int		init_wrapper(t_ms *ms, char **envp);

// tools.c
int		substring_start(char *s1, char *s2);
char	*ms_strjoin(char *s1, char *s2, char c);
int		msg_err(char *s, int ret);

// clean.c
int		clean_ms_wrapper(t_ms *ms);

// cmd.c
// ???

// debug.c
int	dbg_print_env(t_ms *ms);


#endif