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

static bool	is_builtin(char *path)
{
	return (ft_streq(path, "cd")
		|| ft_streq(path, "echo")
		|| ft_streq(path, "env")
		|| ft_streq(path, "exit")
		|| ft_streq(path, "export")
		|| ft_streq(path, "pwd")
		|| ft_streq(path, "unset"));
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

static t_status	setup_heredoc(t_list **tokens, t_redirect *redirect, t_shell *lambda)
{
	t_token	*token;

	token = (*tokens)->content;
	redirect->file_path = heredoc(token, lambda);
	if (!redirect->file_path)
		return (ERROR);
	return (OK);
}

static t_redirect	*get_redirect(t_list **tokens_ptr, t_shell *lambda)
{
	t_redirect	*redirect;
	t_token		*token;
	char		*content;

	redirect = ft_calloc(1, sizeof(*redirect));
	fill_direction(redirect, (*tokens_ptr)->content);
	token = (*tokens_ptr)->content;
	redirect->is_ambiguous = token->is_ambiguous;
	*tokens_ptr = (*tokens_ptr)->next;
	skip_whitespace_tokens(tokens_ptr); // TODO: Try to let the while-loop below naturally do this
	redirect->file_path = ft_strdup("");
	if (!redirect->file_path)
	{
		// TODO: Free
		return (NULL);
	}
	while (*tokens_ptr)
	{
		token = (*tokens_ptr)->content;
		// TODO: Maybe necessary to add check for token being NULL?
		if (!is_text_token(token))
			break ;

		if (token->type == UNQUOTED)
			content = ft_strtrim_whitespace(token->content);
		else
			content = ft_strdup(token->content);
		if (redirect->direction == DIRECTION_HEREDOC)
			setup_heredoc(tokens_ptr, redirect, lambda);
		else
			redirect->file_path = ft_strjoin_and_free_left_right(redirect->file_path, &content);

		if (!redirect->file_path)
		{
			// TODO: Free
			return (NULL);
		}

		*tokens_ptr = (*tokens_ptr)->next;
	}
	return (redirect);
}

static char	*get_path(t_list **tokens_ptr, t_list *env)
{
	char	*path;
	t_token	*token;
	char	*absolute_path;

	path = ft_strdup("");
	if (!path)
	{
		// TODO: Free
		return (NULL);
	}
	while (*tokens_ptr)
	{
		token = (*tokens_ptr)->content;
		// TODO: Maybe necessary to add check for token being NULL?
		if (!is_text_token(token))
			break ;

		path = ft_strjoin_and_free_left(path, token->content);
		if (!path)
		{
			// TODO: Free
			return (NULL);
		}
		*tokens_ptr = (*tokens_ptr)->next;
	}
	if (is_builtin(path) || ft_strchr(path, '/'))
		return (path);
	absolute_path = get_absolute_path_from_env(path, env);
	if (absolute_path == path)
		return (path);
	ft_free(&path);
	return (absolute_path);
}

static char	**get_arg_string_array(t_list *arg_list, char *path)
{
	char	**arg_strings_start;
	char	**arg_strings;

	arg_strings_start = ft_calloc(ft_lstsize(arg_list) + 2, sizeof(*arg_strings));
	arg_strings = arg_strings_start;
	if (!arg_strings)
		return (null(prefixed_perror("get_arg_string_array()")));
	*arg_strings = ft_strdup(path);
	arg_strings++;
	while (arg_list)
	{
		*arg_strings = arg_list->content;
		arg_strings++;
		arg_list = arg_list->next;
	}
	*arg_strings = NULL;
	return (arg_strings_start);
}

static char	*get_arg(t_list **tokens_ptr)
{
	char	*arg;
	t_token	*token;

	arg = ft_strdup("");
	if (!arg)
	{
		// TODO: Free
		return (NULL);
	}
	while (*tokens_ptr)
	{
		token = (*tokens_ptr)->content;
		// TODO: Maybe necessary to add check for token being NULL?
		if (!is_text_token(token))
			break ;
		arg = ft_strjoin_and_free_left(arg, token->content);
		if (!arg)
		{
			// TODO: Free
			return (NULL);
		}
		*tokens_ptr = (*tokens_ptr)->next;
	}
	return (arg);
}

static t_status	fill_cmd(t_list **tokens_ptr, t_shell *lambda, t_cmd *cmd)
{
	t_token		*token;
	t_redirect	*redirect;
	t_list		*arg_list;
	char		*arg;
	char		*arg_zero;

	arg_list = NULL;
	arg_zero = NULL;
	// token = (*tokens_ptr)->content;
	while (*tokens_ptr)
	{
		token = (*tokens_ptr)->content;
		// TODO: Maybe necessary to add check for token being NULL?
		if (token->type == PIPE)
		{
			*tokens_ptr = (*tokens_ptr)->next;
			break ;
		}
		else if (token->type == REDIRECTION)
		{
			redirect = get_redirect(tokens_ptr, lambda);
			if (!redirect || !ft_lstnew_back(&cmd->redirections, redirect))
				return (ERROR);
		}
		else if (is_text_token(token) && !cmd->path)
		{
			arg_zero = token->content;
			cmd->path = get_path(tokens_ptr, lambda->env);
			if (!cmd->path)
				return (ERROR);
		}
		else if (is_text_token(token))
		{
			arg = get_arg(tokens_ptr);
			if (!arg || !ft_lstnew_back(&arg_list, arg))
				return (ERROR);
		}
		else
			*tokens_ptr = (*tokens_ptr)->next;
	}
	if (arg_zero)
	{
		cmd->args = get_arg_string_array(arg_list, arg_zero);
		ft_lstclear(&arg_list, NULL);
	}
	else
	{
		ft_lstclear(&arg_list, NULL);
		return (ERROR);
	}
	return (OK);
}

t_list	*parse(t_list *tokens, t_shell *lambda)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = NULL;
	while (tokens)
	{
		if (alloc_cmd(&cmd) == ERROR || fill_cmd(&tokens, lambda, cmd) == ERROR || !cmd->path || !ft_lstnew_back(&cmds, cmd))
			return (null(dealloc_cmd(&cmd)));
	}
	return (cmds);
}
