/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
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
#include <fcntl.h>
#include <limits.h>

static void	write_tokens_into_file(t_list *tokens, int fd)
{
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		if (token->was_single_quoted)
			ft_putstr_fd("\'", fd);
		else if (token->type == DOUBLE_QUOTED)
			ft_putstr_fd("\"", fd);
		ft_putstr_fd(token->content, fd);
		if (token->was_single_quoted)
			ft_putstr_fd("\'", fd);
		else if (token->type == DOUBLE_QUOTED)
			ft_putstr_fd("\"", fd);
		tokens = tokens->next;
	}
	ft_putstr_fd("\n", fd);
}

static t_status	heredoc_readline_and_write(t_token *delimiter, int fd,
					t_shell *lambda)
{
	t_status	err_status;
	char		*line;
	t_list		*tokens;

	err_status = OK;
	while (err_status == OK)
	{
		line = readline("> ");
		if (line == NULL)
			return (OK);
		if (ft_streq(line, delimiter->content))
			break ;
		tokens = tokenize(line);
		ft_free(&line);
		if (!tokens)
			return (ERROR);
		err_status = expand_heredoc_tokens(delimiter, tokens, lambda);
		if (err_status != ERROR)
			write_tokens_into_file(tokens, fd);
		dealloc_lst(&tokens, dealloc_token);
	}
	ft_free(&line);
	return (err_status);
}

static char	*get_new_heredoc_path(void)
{
	int		iter;
	char	*num;
	char	*file;
	char	*full_path;

	iter = 1;
	while (iter < INT_MAX)
	{
		num = ft_itoa(iter);
		file = ft_strjoin("heredoc_", num);
		ft_free(&num);
		full_path = ft_strjoin("/tmp/", file);
		ft_free(&file);
		if (access(full_path, F_OK))
			break ;
		ft_free(&full_path);
		iter++;
	}
	if (!full_path)
		prefixed_error("No temporary heredoc file could be created\n");
	return (full_path);
}

char	*heredoc(t_token *delimiter, t_shell *lambda)
{
	char	*heredoc_path;
	int		fd;

	heredoc_path = get_new_heredoc_path();
	if (!heredoc_path)
		return (NULL);
	fd = open(heredoc_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		ft_free(&heredoc_path);
	if (heredoc_readline_and_write(delimiter, fd, lambda) == ERROR)
		ft_free(&heredoc_path);
	close(fd);
	return (heredoc_path);
}
