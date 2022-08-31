/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 11:54:27 by mikuiper      ########   odam.nl         */
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

typedef struct s_ms
{
	char	**env;
	char	*input_line;

}			t_ms;

// PROTOTYPES
// INIT.C
int		init_ms(void);
int		init_env(t_ms *ms, char **envp);

// TOOLS.C
int		msg_err(char *s, int ret);

// INPUT.C
void	show_prompt(t_ms *ms);

// CLEAN.C

// BUILTINS.C
int		ms_pwd(void);

// CMD.C

// DEBUG.C

#endif