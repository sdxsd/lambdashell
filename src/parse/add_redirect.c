/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_redirect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 18:15:35 by sbos          #+#    #+#                 */
/*   Updated: 2023/01/12 18:15:35 by sbos          ########   odam.nl         */
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

t_status	add_redirect(t_list **tokens_ptr, t_list **redirections_ptr)
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
