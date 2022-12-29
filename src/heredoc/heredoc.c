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

static char	*create_heredoc_file(void)
{
	int		iter;
	char	*file;
	char	*full_path;
	char	*num;

	iter = 1;
	num = ft_itoa(iter);
	file = ft_strjoin("heredoc_", num);
	full_path = ft_strjoin("/tmp/", file);
	while (!access(full_path, F_OK))
	{
		ft_free(&full_path);
		num = ft_itoa(iter);
		file = ft_strjoin("heredoc_", num);
		full_path = ft_strjoin("/tmp/", file);
		ft_free(&num);
		ft_free(&file);
		iter++;
	}
	return (full_path);
}

static void	convert_single_to_double(t_list *tokens)
{
	t_token	*token;
	while (tokens)
	{
		token = tokens->content;
		token->was_single_quoted = FALSE;
		if (token->type == SINGLE_QUOTED)
		{
			token->was_single_quoted = TRUE;
			token->type = DOUBLE_QUOTED;
		}
		tokens = tokens->next;
	}
}

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

static t_status	heredoc_read_and_write(t_shell *lambda, t_token *delimiter, int fd)
{
	char	*line;
	t_list	*tokens;

	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_putstr("λ: warning: here-document delimited by end-of-file\n");
			return (OK);
		}
		if (ft_streq(line, delimiter->content))
		{
			ft_free(&line);
			break ;
		}
		tokens = tokenize(line);
		if (!tokens)
		{
			ft_free(&line);
			return (ERROR);
		}
		convert_single_to_double(tokens);
		if (delimiter->type != SINGLE_QUOTED && delimiter->type != DOUBLE_QUOTED)
		{
			if (expand_variables(tokens, lambda) == ERROR)
			{
				ft_free(&line);
				dealloc_lst(&tokens, dealloc_token);
				return (ERROR);
			}
		}
		write_tokens_into_file(tokens, fd);
		dealloc_lst(&tokens, dealloc_token);
	}
	return (OK);
}

char	*heredoc(t_token *delimiter, t_shell *lambda)
{
	char	*full_path;
	int		fd;

	full_path = create_heredoc_file();
	fd = open(full_path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		return (NULL);
	heredoc_read_and_write(lambda, delimiter, fd);
	close(fd);
	return (full_path);
}
