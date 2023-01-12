/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
THIS FILE IS LICENSED UNDER THE GNU GPLv3
Copyright (C) 2022  Will Maguire

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>

The definition of Free Software is as follows:
				- The freedom to run the program, for any purpose.
				- The freedom to study how the program works, and adapt it to your needs.
				- The freedom to redistribute copies so you can help your neighbor.
				- The freedom to improve the program, and release
				your improvements to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include "../../include/minishell.h"
#include <stdio.h>

/* void	dbg_print_tokens(t_list *tokens) */
/* { */
/* 	char	*token_type_strings[] = { */
/* 		[SINGLE_QUOTED] = "SINGLE_QUOTED", */
/* 		[DOUBLE_QUOTED] = "DOUBLE_QUOTED", */
/* 		[REDIRECTION] = "REDIRECTION", */
/* 		[HEREDOC] = "HEREDOC", */
/* 		[PIPE] = "PIPE", */
/* 		[WHITESPACE] = "WHITESPACE", */
/* 		[UNQUOTED] = "UNQUOTED", */
/* 	}; */
/* 	t_token	*token; */
/* 	char	*content; */

/* 	printf("+---------------+---------------------+--------------+\n"); */
/* 	printf("| token type    | token content       | is ambiguous |\n"); */
/* 	printf("+---------------+---------------------+--------------+\n"); */
/* 	while (tokens) */
/* 	{ */
/* 		token = tokens->content; */
/* 		printf("| %-13s ", token_type_strings[token->type]); */
		/* content = \ */
		/* 	ft_strjoin_array((char *[]){"[", token->content, "]", NULL}); */
/* 		printf("| %-20s", content); */
/* 		printf("| %d            |\n", token->is_ambiguous); */
/* 		printf("+---------------+---------------------+--------------+\n"); */
/* 		tokens = tokens->next; */
/* 	} */
/* } */

/* void	dbg_print_commands(t_list *cmds) */
/* { */
/* 	char	*direction_strings[4]; */
/* 	size_t	cmd_index; */
/* 	t_cmd	*cmd; */
/* 	char	**arg_array; */
/* 	size_t	redirection_index; */
/* 	t_list	*redirection_list; */
/* 	t_redirect	*redirection; */

/* 	direction_strings[DIRECTION_HEREDOC] = "HEREDOC", */
/* 	direction_strings[DIRECTION_APPEND] = "APPEND", */
/* 	direction_strings[DIRECTION_IN] = "IN", */
/* 	direction_strings[DIRECTION_OUT] = "OUT", */
/* 	printf("\n"); */
/* 	cmd_index = 0; */
/* 	while (cmds) */
/* 	{ */
/* 		printf("Command %zu:\n", cmd_index + 1); */
/* 		cmd = cmds->content; */
/* 		printf("\tInput file descriptor: %i\n", cmd->input_fd); */
/* 		printf("\tOutput file descriptor: %i\n", cmd->output_fd); */
/* 		printf("\tPath: [%s]\n", cmd->path); */
/* 		printf("\tArgs:"); */
/* 		arg_array = cmd->args; */
/* 		while (*arg_array) */
/* 		{ */
/* 			printf(" [%s]", *arg_array); */
/* 			arg_array++; */
/* 		} */
/* 		printf("\n"); */
/* 		redirection_index = 0; */
/* 		redirection_list = cmd->redirections; */
/* 		while (redirection_list) */
/* 		{ */
/* 			printf("\tRedirection %zu:\n", redirection_index + 1); */
/* 			redirection = redirection_list->content; */
/* 			printf("\t\tRedirection file path: [%s]\n", redirection->filepath); */
			/* printf("\t\tRedirection direction: %s\n",\ */
			/* 	   direction_strings[redirection->direction]); */
/* 			printf("\t\tIs ambiguous: %i\n", redirection->is_ambiguous); */
/* 			redirection_list = redirection_list->next; */
/* 			redirection_index++; */
/* 		} */
/* 		cmds = cmds->next; */
/* 		cmd_index++; */
/* 		printf("\n"); */
/* 	} */
/* } */
