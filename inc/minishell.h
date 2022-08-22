/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/22 12:51:08 by mikuiper      ########   odam.nl         */
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

// parse_cmd.c

// run_cmd.c



#endif