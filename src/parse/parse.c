/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 16:58:21 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/24 16:58:21 by sbos          ########   odam.nl         */
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

static t_cmd	*get_initial_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->i_fd = STDIN_FILENO;
	cmd->o_fd = STDOUT_FILENO;
	// cmd->args = NULL;
	// cmd->path = NULL;
	// cmd->redirection = NULL;
	// cmd->has_ambiguous_redirect = false;
	return (cmd);
}

static t_redirect	*get_redirect(t_list **tokens)
{
	t_redirect	*redirect;
	t_token		*token;

	redirect = ft_calloc(1, sizeof(*redirect));

	token = (*tokens)->content;
	// TODO: Handle << and >> properly
	if (*token->content == '<')
		redirect->direction = IN;
	else if (*token->content == '>')
		redirect->direction = OUT;

	*tokens = (*tokens)->next;

	while (*tokens)
	{
		token = (*tokens)->content;
		// TODO: Maybe necessary to add check for token being NULL?
		if (token && token->type != WHITESPACE)
			break ;
		*tokens = (*tokens)->next;
	}

	while (*tokens)
	{
		token = (*tokens)->content;

		// TODO: Maybe necessary to add check for token being NULL?
		if (token->type != SINGLE_QUOTED && token->type != DOUBLE_QUOTED && token->type != UNQUOTED)
			break;

		*tokens = (*tokens)->next;
	}

	return (redirect);
}

static t_cmd	*get_cmd(t_list **tokens)
{
	t_cmd		*cmd;
	t_token		*token;
	t_redirect	*redirect;

	cmd = get_initial_cmd();
	while (*tokens)
	{
		token = (*tokens)->content;

		if (token->type == PIPE)
		{
			*tokens = (*tokens)->next;
			break ;
		}
		else if (token->type == REDIRECTION)
		{
			if (is_ambiguous_redirect(*tokens))
				cmd->has_ambiguous_redirect = true;

			redirect = get_redirect(tokens);
			if (!redirect || !ft_lstnew_back(&cmd->redirections, redirect))
			{
				// TODO: Free
				return (NULL);
			}
		}
		else
			*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_list	*parse(t_list *tokens)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = NULL;

	while (tokens)
	{
		cmd = get_cmd(&tokens);
		if (!cmd || !ft_lstnew_back(&cmds, cmd))
			return (NULL); // TODO: Free?
	}

	return (cmds);
}
