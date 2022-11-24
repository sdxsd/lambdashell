/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 17:08:18 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/18 17:08:18 by sbos          ########   odam.nl         */
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

// int	is_builtin(char *line)
// {
// 	char	**split_line;

// 	split_line = ft_split(line, ' ');
// 	if (!split_line)
// 		return (msg_err("is_builtin()", FAILURE));
// 	if (ft_streq(split_line[0], "cd") || \
// 		ft_streq(split_line[0], "echo") || \
// 		ft_streq(split_line[0], "env") || \
// 		ft_streq(split_line[0], "export") || \
// 		ft_streq(split_line[0], "pwd") || \
// 		ft_streq(split_line[0], "unset"))
// 	{
// 		free_ptr_array(split_line);
// 		return (TRUE);
// 	}
// 	else
// 	{
// 		free_ptr_array(split_line);
// 		return (FALSE);
// 	}
// }

// int	is_command(char *line, t_vector *env)
// {
// 	char	**split_line;
// 	char	*path;

// 	split_line = ft_split(line, ' ');
// 	if (!split_line)
// 		return (msg_err("is_command()", FAILURE));
// 	if (ft_strnstr(split_line[0], "/", ft_strlen(split_line[0])))
// 		path = split_line[0];
// 	else
// 		path = get_path(split_line[0], env);
// 	free_ptr_array(split_line);
// 	if (!path)
// 		return (FALSE);
// 	else
// 	{
// 		if (!ft_strnstr(path, "/", ft_strlen(path)))
// 			ft_free(&path);
// 		return (TRUE);
// 	}
// }

// int	get_type(char *line, t_vector *env)
// {
// 	if (is_builtin(line))
// 		return (tkn_bltin);
// 	else if (is_command(line, env))
// 		return (tkn_cmd);
// 	else
// 		return (msg_err(line, -1));
// }

// t_exec_element	*tokenize(t_shell *lambda)
// {
// 	t_exec_element	*exec_list;
// 	t_exec_element	*prev;
// 	t_exec_element	*curr;
// 	int				iter;

// 	iter = 1;
// 	exec_list = new_exec_element();
// 	if (!exec_list)
// 		return (null_msg_err("tokenize()"));
// 	exec_list->type = get_type(lambda->lines[0], lambda->env);
// 	if (exec_list->type == -1)
// 	{
// 		dealloc_exec_list(exec_list);
// 		return (null_msg_err("tokenize()"));
// 	}
// 	exec_list->line = lambda->lines[0];
// 	prev = exec_list;
// 	while (lambda->lines[iter])
// 	{
// 		curr = new_exec_element();
// 		if (!curr)
// 		{
// 			free_exec_list(exec_list);
// 			return (null_msg_err("tokenize()"));
// 		}
// 		curr->type = get_type(lambda->lines[iter], lambda->env);
// 		if (exec_list->type == -1)
// 		{
// 			dealloc_exec_list(exec_list);
// 			return (null_msg_err("tokenize()"));
// 		}
// 		curr->line = lambda->lines[iter];
// 		prev->next = curr;
// 		prev = curr;
// 		iter++;
// 	}
// 	return (exec_list);
// }

static t_token_type	subtokenize(char **line)
{
	if (**line == '\'')
		return (subtokenize_single_quote(line));
	else if (**line == '"')
		return (subtokenize_double_quote(line));
	else if (**line == '<' || **line == '>')
		return (subtokenize_redirection(line));
	else if (ft_isspace(**line))
		return (subtokenize_whitespace(line));
	else
		return (subtokenize_unquoted(line));
}

t_list	*tokenize(char *line)
{
	t_list			*tokens;
	char			*old_line_pos;
	t_token_type	token_type;
	char			*content;
	t_token			*token;

	tokens = NULL;

	while (*line)
	{
		old_line_pos = line;

		token_type = subtokenize(&line);

		if (token_type == SINGLE_QUOTED || token_type == DOUBLE_QUOTED)
			content = ft_substr(old_line_pos, 1, line - old_line_pos - 2);
		else
			content = ft_substr(old_line_pos, 0, line - old_line_pos);

		if (!content)
			return (NULL); // TODO: Free?

		token = get_token(token_type, content);
		if (!token || !ft_lstnew_back(&tokens, token))
			return (NULL); // TODO: Free?
	}

	return (tokens);
}
