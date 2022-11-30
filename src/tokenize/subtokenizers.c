/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subtokenizers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 17:08:28 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/18 17:08:28 by sbos          ########   odam.nl         */
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

t_token_type	subtokenize_single_quote(char **line_ptr)
{
	(*line_ptr)++;
	while (**line_ptr != '\0' && **line_ptr != '\'')
		(*line_ptr)++;
	if (**line_ptr == '\'')
		(*line_ptr)++;
	return (SINGLE_QUOTED);
}

t_token_type	subtokenize_double_quote(char **line_ptr)
{
	(*line_ptr)++;
	while (**line_ptr != '\0' && **line_ptr != '"')
		(*line_ptr)++;
	if (**line_ptr == '"')
		(*line_ptr)++;
	return (DOUBLE_QUOTED);
}

t_token_type	subtokenize_heredoc(char **line_ptr)
{
	(*line_ptr) += 2;
	return (REDIRECTION);
}

t_token_type	subtokenize_append(char **line_ptr)
{
	(*line_ptr) += 2;
	return (REDIRECTION);
}

t_token_type	subtokenize_redirection(char **line_ptr)
{
	(*line_ptr)++;
	return (REDIRECTION);
}

t_token_type	subtokenize_pipe(char **line_ptr)
{
	(*line_ptr)++;
	return (PIPE);
}

t_token_type	subtokenize_whitespace(char **line_ptr)
{
	while (**line_ptr != '\0' && ft_isspace(**line_ptr))
		(*line_ptr)++;
	return (WHITESPACE);
}

t_token_type	subtokenize_unquoted(char **line_ptr)
{
	// TODO: Make sure this isn't missing any conditions for breaking
	while (**line_ptr != '\0' && !ft_isspace(**line_ptr) && **line_ptr != '|' && **line_ptr != '<' && **line_ptr != '>' && **line_ptr != '"' && **line_ptr != '\'')
		(*line_ptr)++;
	return (UNQUOTED);
}
