/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/14 13:40:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* HEADERS */
# include "structs.h"
# include "prototypes.h"
# include "splash.h"

/* LIBRARIES */
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* DEFINES */
# define READ 0
# define WRITE 1
# define TRUE 1
# define FALSE 0
# define FAILURE 1
# define SUCCESS 0

/* GLOBAL VARIABLE */
/* int		global_sig; */

#endif