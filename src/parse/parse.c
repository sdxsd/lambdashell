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

static int	is_builtin(char *path)
{
	return (ft_streq(path, "cd")
		|| ft_streq(path, "echo")
		|| ft_streq(path, "env")
		|| ft_streq(path, "export")
		|| ft_streq(path, "pwd")
		|| ft_streq(path, "unset")
		|| ft_streq(path, "exit"));
}

static t_cmd	*get_initial_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->i_fd = STDIN_FILENO;
	cmd->o_fd = STDOUT_FILENO;
	return (cmd);
}

static void	fill_direction(t_redirect *redirect, t_token *token)
{
	if (*token->content == '<' && token->content[1] == '<')
		redirect->direction = DIRECTION_HEREDOC;
	else if (*token->content == '>' && token->content[1] == '>')
		redirect->direction = DIRECTION_APPEND;
	else if (*token->content == '<')
		redirect->direction = DIRECTION_IN;
	else if (*token->content == '>')
		redirect->direction = DIRECTION_OUT;
}

static t_redirect	*get_redirect(t_list **tokens)
{
	t_redirect	*redirect;
	t_token		*token;

	redirect = ft_calloc(1, sizeof(*redirect));

	fill_direction(redirect, (*tokens)->content);

	*tokens = (*tokens)->next;

	skip_whitespace_tokens(tokens);

	redirect->file_path = ft_calloc(1, sizeof(*redirect->file_path));
	if (!redirect->file_path)
	{
		// TODO: Free
		return (NULL);
	}

	redirect->is_ambiguous = is_ambiguous_redirect(*tokens);

	while (*tokens)
	{
		token = (*tokens)->content;

		// TODO: Maybe necessary to add check for token being NULL?
		if (!is_text_token(token))
			break;

		redirect->file_path = ft_strjoin_and_free_left(redirect->file_path, token->content);
		if (!redirect->file_path)
		{
			// TODO: Free
			return (NULL);
		}

		*tokens = (*tokens)->next;
	}

	return (redirect);
}

static char		*get_path(t_list **tokens, t_list *env)
{
	char	*path;
	t_token	*token;
	char	*absolute_path;

	path = ft_calloc(1, sizeof(*path));
	if (!path)
	{
		// TODO: Free
		return (NULL);
	}

	while (*tokens)
	{
		token = (*tokens)->content;

		// TODO: Maybe necessary to add check for token being NULL?
		if (!is_text_token(token))
			break;

		path = ft_strjoin_and_free_left(path, token->content);
		if (!path)
		{
			// TODO: Free
			return (NULL);
		}

		*tokens = (*tokens)->next;
	}
	if (is_builtin(path) || ft_strchr(path, '/'))
		return (path);
	absolute_path = get_absolute_path_from_env(path, env);
	ft_free(&path);
	return (absolute_path);
}

static char		*get_arg(t_list **tokens)
{
	char	*arg;
	t_token	*token;

	arg = ft_calloc(1, sizeof(*arg));
	if (!arg)
	{
		// TODO: Free
		return (NULL);
	}

	while (*tokens)
	{
		token = (*tokens)->content;

		// TODO: Maybe necessary to add check for token being NULL?
		if (!is_text_token(token))
			break;

		arg = ft_strjoin_and_free_left(arg, token->content);
		if (!arg)
		{
			// TODO: Free
			return (NULL);
		}

		*tokens = (*tokens)->next;
	}
	return (arg);
}

static t_cmd	*get_cmd(t_list **tokens, t_list *env)
{
	t_cmd		*cmd;
	t_token		*token;
	t_redirect	*redirect;
	char		*arg;

	cmd = get_initial_cmd();
	while (*tokens)
	{
		token = (*tokens)->content;

		// TODO: Maybe necessary to add check for token being NULL?

		if (token->type == PIPE)
		{
			*tokens = (*tokens)->next;
			break ;
		}
		else if (token->type == REDIRECTION)
		{
			redirect = get_redirect(tokens);
			if (!redirect || !ft_lstnew_back(&cmd->redirections, redirect))
			{
				// TODO: Free
				return (NULL);
			}
		}
		else if (is_text_token(token) && !cmd->path)
		{
			cmd->path = get_path(tokens, env);
			if (!cmd->path)
			{
				// TODO: Free
				return (NULL);
			}
		}
		else if (is_text_token(token))
		{
			arg = get_arg(tokens);
			if (!arg || !ft_lstnew_back(&cmd->args, arg))
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

t_list	*parse(t_list *tokens, t_list *env)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = NULL;

	while (tokens)
	{
		cmd = get_cmd(&tokens, env);
		if (!cmd || !ft_lstnew_back(&cmds, cmd))
			return (NULL); // TODO: Free?
	}

	return (cmds);
}
