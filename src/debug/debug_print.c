/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CODAM C FILE                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire     ########   codam.nl         */
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

void	dbg_print_redirec(t_redirec *redir)
{
	printf("FILE PATH: %s\n", redir->file_path);

	if (redir->direction == IN)
		printf("DIRECTION = IN\n");
	if (redir->direction == OUT)
		printf("DIREC = OUT\n");
	else if (redir->direction == APPEND)
		printf("DIREC = APPEND\n");
}

void	dbg_print_cmd(t_cmd	*cmd)
{
	printf("PATH: %s\n", cmd->path);
	printf("LINES:\n");
	dbg_print_lines(cmd->args);
	printf("I_FD: %d\n", cmd->i_fd);
	printf("O_FD: %d\n", cmd->o_fd);
	if (cmd->redir)
		dbg_print_redirec(cmd->redir);
}

void	dbg_print_lines(char **lines)
{
	int	iter;

	iter = 0;
	while (lines[iter])
	{
		printf("%d: %s\n", iter, lines[iter]);
		iter++;
	}
}

// /* NOTE: To be called after running the tokenize() function. */
// void	dbg_print_exec_list(t_exec_element *head)
// {
// 	if (head->type == tkn_cmd)
// 		printf("Type: [cmd]\n");
// 	else if (head->type == tkn_bltin)
// 		printf("Type: [builtin]\n");
// 	else
// 		printf("Type: [unknown]\n");
// 	printf("Line: %s\n", head->line);
// 	printf("Value: %p\n", head->value);
// 	printf("next: %p\n\n", head->next);
// 	if (head->next)
// 		dbg_print_exec_list(head->next);
// }

void	dbg_print_env(t_vector *head)
{
	t_env_element	*ee;

	ee = head->data;
	printf("%s%s\n", ee->key, ee->val);
	if (head->next)
		dbg_print_env(head->next);
	else
		return ;
}

void	dbg_print_tokens(t_list *tokens)
{
	char	*token_type_strings[] = {
		[SINGLE_QUOTED] = "SINGLE_QUOTED",
		[DOUBLE_QUOTED] = "DOUBLE_QUOTED",
		[REDIRECTION] = "REDIRECTION",
		[PIPE] = "PIPE",
		[WHITESPACE] = "WHITESPACE",
		[UNQUOTED] = "UNQUOTED",
	};
	t_token	*token;
	char	*str;

	printf("+---------------+---------------------+\n");
	printf("| token type    | token content       |\n");
	printf("+---------------+---------------------+\n");

	while (tokens)
	{
		token = tokens->content;

		printf("| %-13s ", token_type_strings[token->type]);

		asprintf(&str, "[%s]", token->content);
		printf("| %-19s |\n", str);
		ft_free(&str);

		printf("+---------------+---------------------+\n");

		tokens = tokens->next;
	}
}

void	dbg_print_commands(t_list *cmds)
{
	// char	*direction_strings[] = {
	// 	[IN] = "IN",
	// 	[OUT] = "OUT",
	// 	[APPEND] = "APPEND",
	// };
	t_cmd	*cmd;
	size_t	cmd_index;

	cmd_index = 0;
	while (cmds)
	{
		printf("Command %zu:\n", cmd_index);

		cmd = cmds->content;

		printf("Input file descriptor: %i\n", cmd->i_fd);
		printf("Output file descriptor: %i\n", cmd->o_fd);

		// printf("Args: %s\n", arg);

		printf("Path: %s\n", cmd->path);

		// printf("Redirection[0] file_path: %s\n", cmd->redir[0].file_path);
		// printf("Redirection[0] direction: %s\n", direction_strings[cmd->redir[0].direction]);

		// printf("Redirection[1] file_path: %s\n", cmd->redir[1].file_path);
		// printf("Redirection[1] direction: %s\n", direction_strings[cmd->redir[1].direction]);

		printf("Has ambiguous redirect: %i\n", cmd->has_ambiguous_redirect);

		cmds = cmds->next;
		cmd_index++;
		printf("\n");
	}
}
