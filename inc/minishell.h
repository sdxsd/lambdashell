/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/22 16:50:57 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> // PRINTF TIJDELIJK
# include "../libft/libft.h"

#include <readline/readline.h>
#include <readline/history.h>

// GLOBAL VARIABLE
char    **env_global;

// PROTOTYPES
// init.c
int	init(char **envp);
int	init_global(char **envp);
int	env_find_key(char *key);
int	substring_start(char *s1, char *s2);

int	env_add_keyvalue(char *key, char *value);
int	env_find_key(char *key);

// parse_cmd.c

// run_cmd.c



#endif