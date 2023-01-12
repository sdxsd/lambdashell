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

static char	**get_arg_string_array(t_list *arg_list)
{
	char	**arg_strings;
	char	**arg_strings_start;

	arg_strings = ft_calloc(ft_lstsize(arg_list) + 1,
			sizeof(*arg_strings));
	if (!arg_strings)
		return (null(prefixed_perror("get_arg_string_array()")));
	arg_strings_start = arg_strings;
	if (arg_list->content)
		*arg_strings = ft_strdup(arg_list->content);
	arg_list = arg_list->next;
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
		return (NULL);
	while (*tokens_ptr)
	{
		token = (*tokens_ptr)->content;
		if (!is_text_token(token))
			break ;
		arg = ft_strjoin_and_free_left(arg, token->content);
		if (!arg)
			return (NULL);
		*tokens_ptr = (*tokens_ptr)->next;
	}
	return (arg);
}

static t_status	add_arg(t_list **arg_list_ptr, t_list **tokens_ptr)
{
	char	*arg;

	arg = get_arg(tokens_ptr);
	if (!arg || !ft_lstnew_back(arg_list_ptr, arg))
		return (ERROR);
	return (OK);
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

static char	*get_redirect_filepath(t_list **tokens_ptr)
{
	t_token		*token;
	char		*filepath;
	char		*content;

	token = (*tokens_ptr)->content;
	filepath = ft_strdup("");
	if (!filepath)
		return (NULL);
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
		filepath = ft_strjoin_and_free_left_right(filepath, &content);
		if (!filepath)
			return (NULL);
		*tokens_ptr = (*tokens_ptr)->next;
	}
	return (filepath);
}

static t_status	add_redirect(t_list **tokens_ptr, t_list **redirections_ptr)
{
	t_direction	direction;
	bool		is_ambiguous;
	char		*filepath;
	t_redirect	*redirect;

	direction = get_direction((*tokens_ptr)->content);
	is_ambiguous = ((t_token *)(*tokens_ptr)->content)->is_ambiguous;
	filepath = get_redirect_filepath(tokens_ptr);
	if (!filepath)
		return (ERROR);
	redirect = alloc_redirect(filepath, direction, is_ambiguous);
	if (!redirect || !ft_lstnew_back(redirections_ptr, redirect))
		return (dealloc_redirect(&redirect));
	return (OK);
}

static t_status	add_next_cmd_part(t_list **tokens_ptr, t_cmd *cmd, t_list *env,
					t_list **arg_list_ptr)
{
	t_token	*token;

	token = (*tokens_ptr)->content;
	if (token->type == REDIRECTION || token->type == HEREDOC)
	{
		if (add_redirect(tokens_ptr, &cmd->redirections) == ERROR)
			return (ERROR);
	}
	else if (is_text_token(token) && !cmd->path)
	{
		if (add_arg(arg_list_ptr, tokens_ptr) == ERROR)
			return (ERROR);
		cmd->path = get_path(ft_strdup((char *)(*arg_list_ptr)->content), env);
		if (!cmd->path)
			return (ERROR);
	}
	else if (is_text_token(token) && ft_str_not_set(token->content,
			WHITESPACE_CHARACTERS))
	{
		if (add_arg(arg_list_ptr, tokens_ptr) == ERROR)
			return (ERROR);
	}
	else
		*tokens_ptr = (*tokens_ptr)->next;
	return (OK);
}

static t_status	fill_cmd(t_list **tokens_ptr, t_list *env, t_cmd *cmd)
{
	t_list	*arg_list;

	arg_list = NULL;
	while (*tokens_ptr)
	{
		if (((t_token *)(*tokens_ptr)->content)->type == PIPE)
		{
			*tokens_ptr = (*tokens_ptr)->next;
			break ;
		}
		if (add_next_cmd_part(tokens_ptr, cmd, env, &arg_list) == ERROR)
			return (ERROR);
	}
	if (arg_list)
		cmd->args = get_arg_string_array(arg_list);
	ft_lstclear(&arg_list, NULL);
	return (OK);
}

t_list	*parse(t_list *tokens, t_list *env)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = NULL;
	while (tokens)
	{
		if (alloc_cmd(&cmd) == ERROR || fill_cmd(&tokens, env, cmd) == ERROR
			|| !ft_lstnew_back(&cmds, cmd))
			return (null(dealloc_cmd(&cmd)));
	}
	return (cmds);
}
