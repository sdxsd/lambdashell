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

static char	**get_arg_string_array(char *arg_zero, t_list *arg_list)
{
	char	**arg_strings_start;
	char	**arg_strings;

	arg_strings_start = ft_calloc(ft_lstsize(arg_list) + 2, sizeof(*arg_strings));
	arg_strings = arg_strings_start;
	if (!arg_strings)
		return (null(prefixed_perror("get_arg_string_array()")));
	if (arg_zero)
		*arg_strings = ft_strdup(arg_zero);
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

static char	*get_path(char *arg_zero, t_list *env)
{
	char	*absolute_path;

	if (is_builtin(arg_zero) || ft_strchr(arg_zero, '/'))
		return (arg_zero);
	absolute_path = get_absolute_path_from_env(arg_zero, env);
	if (absolute_path == arg_zero)
		return (arg_zero);
	ft_free(&arg_zero);
	return (absolute_path);
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

static t_direction	get_direction(t_token *token)
{
	if (*token->content == '<' && token->content[1] == '<')
		return (DIRECTION_HEREDOC);
	if (*token->content == '>' && token->content[1] == '>')
		return (DIRECTION_APPEND);
	if (*token->content == '<')
		return (DIRECTION_IN);
	return (DIRECTION_OUT);
}

static t_redirect	*get_redirect(t_list **tokens_ptr)
{
	t_token		*token;
	char		*file_path;
	t_redirect	*redirect;
	char		*content;

	token = (*tokens_ptr)->content;
	file_path = ft_strdup("");
	if (!file_path)
		return (NULL);
	redirect = alloc_redirect(file_path, get_direction(token),
			token->is_ambiguous);
	if (!redirect)
		return (null(dealloc_redirect(&redirect)));
	*tokens_ptr = (*tokens_ptr)->next;
	skip_whitespace_tokens(tokens_ptr);
	while (*tokens_ptr)
	{
		token = (*tokens_ptr)->content;
		if (!is_text_token(token))
			break ;

		if (token->type == UNQUOTED)
			content = ft_strtrim_whitespace(token->content);
		else
			content = ft_strdup(token->content);
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

static t_status	fill_cmd(t_list **tokens_ptr, t_shell *lambda, t_cmd *cmd)
{
	t_token		*token;
	t_redirect	*redirect;
	t_list		*arg_list;
	char		*arg;
	char		*arg_zero;

	arg_list = NULL;
	arg_zero = NULL;
	while (*tokens_ptr)
	{
		token = (*tokens_ptr)->content;
		if (token->type == PIPE)
		{
			*tokens_ptr = (*tokens_ptr)->next;
			break ;
		}
		else if (token->type == REDIRECTION || token->type == HEREDOC)
		{
			redirect = get_redirect(tokens_ptr);
			if (!redirect || !ft_lstnew_back(&cmd->redirections, redirect))
				return (ERROR);
		}
		else if (is_text_token(token) && !cmd->path)
		{
			arg_zero = get_arg(tokens_ptr);
			cmd->path = get_path(ft_strdup(arg_zero), lambda->env);
			if (!cmd->path)
				return (ERROR);
		}
		else if (is_text_token(token) && ft_str_not_set(token->content, WHITESPACE_CHARACTERS))
		{
			arg = get_arg(tokens_ptr);
			if (!arg || !ft_lstnew_back(&arg_list, arg))
				return (ERROR);
		}
		else
			*tokens_ptr = (*tokens_ptr)->next;
	}
	cmd->args = get_arg_string_array(arg_zero, arg_list);
	ft_free(&arg_zero);
	ft_lstclear(&arg_list, NULL);
	return (OK);
}

t_list	*parse(t_list *tokens, t_shell *lambda)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = NULL;
	while (tokens)
	{
		if (alloc_cmd(&cmd) == ERROR || fill_cmd(&tokens, lambda, cmd) == ERROR
			|| !ft_lstnew_back(&cmds, cmd))
			return (null(dealloc_cmd(&cmd)));
	}
	return (cmds);
}
