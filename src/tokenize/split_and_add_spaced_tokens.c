/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_and_add_spaced_tokens.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/30 19:33:05 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/30 19:33:05 by sbos          ########   odam.nl         */
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

static t_status	new_unquoted_token_back(t_list **current_ptr, char *content,
				t_token_type token_type)
{
	char	*token_content;
	t_token	*token;

	token_content = ft_strdup(content);
	if (!token_content)
		return (ERROR);
	token = alloc_token(token_type, token_content);
	if (!token)
	{
		ft_free(&token_content);
		return (ERROR);
	}
	if (!ft_lstnew_back(current_ptr, token))
		return (dealloc_token(&token));
	return (OK);
}

static t_status	new_space_token_back(t_list *current)
{
	return (new_unquoted_token_back(&current, " ", WHITESPACE));
	// return (new_unquoted_token_back(&current, " ", UNQUOTED));
}

static t_status	try_add_trailing_space(size_t split_count,
					t_token *token, t_list *current)
{
	if (split_count > 0 && ft_strchr(WHITESPACE_CHARACTERS,
			token->content[ft_strlen(token->content) - 1])
		&& new_space_token_back(current) == ERROR)
		return (ERROR);
	return (OK);
}

static t_status	try_add_leading_space(size_t split_index, t_token *token,
					t_list *current)
{
	if ((split_index > 0 || ft_strchr(WHITESPACE_CHARACTERS,
				*token->content)) && new_space_token_back(current) == ERROR)
		return (ERROR);
	return (OK);
}

t_status	split_and_add_spaced_tokens(t_token *token, t_list *current)
{
	char	**split;
	size_t	split_index;
	size_t	split_count;

	split = ft_split_set(token->content, WHITESPACE_CHARACTERS);
	if (!split)
		return (ERROR);
	split_index = 0;
	split_count = ft_ptr_array_len((void **)split);
	while (split_index < split_count)
	{
		if (try_add_leading_space(split_index, token, current) == ERROR)
			return (ERROR);
		if (new_unquoted_token_back(&current, split[split_index],
				UNQUOTED) == ERROR)
			return (ERROR);
		split_index++;
	}
	dealloc_ptr_array(&split);
	if (try_add_trailing_space(split_count, token, current) == ERROR)
		return (ERROR);
	dealloc_token(&token);
	return (OK);
}

// TODO: IMPLEMENT
// [ 'echo', @, 'hello', @, >, @, '', $whitespace_left, @, '', @, $space, @, '', $empty, @, $whitespace_left, $whitespace_left ]
// [ 'echo' ] # input
// [ 'echo' ] # split unquoted
// [ 'echo' ] # discard empty
// [ 'echo' ] # trim whitespace tokens
// [ 'echo' ] # unempty if one token was quoted
// [ 'echo', @, 'hello', @, >, @, '', $whitespace_left, @, '', @, $space, @, '', $empty, @, $whitespace_left, $whitespace_left ]
//            [ 'hello' ] # input
//            [ 'hello' ] # split unquoted
//            [ 'hello' ] # discard empty
//            [ 'hello' ] # trim whitespace tokens
//            [ 'hello' ] # unempty if one token was quoted
// [ 'echo', @, 'hello', @, >, @, '', $whitespace_left, @, '', @, $space, @, '', $empty, @, $whitespace_left, $whitespace_left ]
//                       [ '>' ] # input
//                       [ '>' ] # split unquoted
//                       [ '>' ] # discard empty
//                       [ '>' ] # trim whitespace tokens
//                       [ '>' ] # unempty if one token was quoted
// [ 'echo', @, 'hello', @, >, @, '', $whitespace_left, @, '', @, $space, @, '', $empty, @, $whitespace_left, $whitespace_left ]
//                              [ '', $whitespace_left ] # input           Y
//                              [ '', @, 'b' ] # split unquoted            Y
//                              [  @, 'b' ] # discard empty                N
//                              [ 'b' ] # trim whitespace tokens           N?
//                              [ 'b' ] # unempty if one token was quoted  N
// [ 'echo', @, 'hello', @, >, @, 'b', @, '', @, $space, @, '', $empty, @, $whitespace_left, $whitespace_left ]
//                                      [ '' ] # input
//                                      [ '' ] # split unquoted
//                                      [  ] # discard empty
//                                      [  ] # trim whitespace tokens
//                                      [ '' ] # unempty if one token was quoted
// [ 'echo', @, 'hello', @, >, @, 'b', @, '', @, $space, @, '', $empty, @, $whitespace_left, $whitespace_left ]
//                                             [ $space ] # input
//                                             [ @, ] # split unquoted
//                                             [ @, ] # discard empty
//                                             [  ] # trim whitespace tokens
//                                             [  ] # unempty if one token was quoted
// [ 'echo', @, 'hello', @, >, @, 'b', @, '', @, @, '', $empty, @, $whitespace_left, $whitespace_left ]
//                                                [ '', $empty ] # input
//                                                [ '' ] # split unquoted
//                                                [  ] # discard empty
//                                                [  ] # trim whitespace tokens
//                                                [ '' ] # unempty if one token was quoted
// [ 'echo', @, 'hello', @, >, @, 'b', @, '', @, @, '', @, $whitespace_left, $whitespace_left ]
//                                                    [ $whitespace_left, $whitespace_left ] # input
//                                                    [ @, 'b', @, 'b' ] # split unquoted
//                                                    [ @, 'b', @, 'b' ] # discard empty
//                                                    [ 'b', @, 'b' ] # trim whitespace tokens
//                                                    [ 'b', @, 'b' ] # unempty if one token was quoted
// [ 'echo', @, 'hello', @, >, @, 'b', @, '', @, @, '', @, 'b', @, 'b' ]
// TODO: maybe remove duplicate spaces
