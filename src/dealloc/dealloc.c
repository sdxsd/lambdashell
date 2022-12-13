/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dealloc.c                                          :+:    :+:            */
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

void	dealloc_cmds(t_list *cmds)
{
	t_cmd	*cmd;
	t_list	*tmp;

	while (cmds)
	{
		cmd = cmds->content;
		ft_free(&cmd->args);
		ft_free(&cmd->path);
		if (cmd->redirections)
			dealloc_redirections(cmd->redirections);
		tmp = cmds;
		cmds = cmds->next;
		ft_free(&tmp);
	}
}

int	dealloc_env_element(void *env_element_ptr)
{
	t_env_element	**_env_element_ptr;
	t_env_element	*env_element;

	_env_element_ptr = env_element_ptr;
	env_element = *_env_element_ptr;
	ft_free(&env_element->key);
	ft_free(&env_element->val);
	ft_free(_env_element_ptr);
	return (FAILURE);
}

void	dealloc_lambda(t_shell *lambda)
{
	if (lambda->env)
		ft_lstclear(&lambda->env, dealloc_env_element);
	if (lambda->line)
		ft_free(&lambda->line);
}

void	dealloc_ptr_array(void *ptr_array_ptr)
{
	void	***_ptr_array_ptr;
	void	**ptr_array;

	_ptr_array_ptr = ptr_array_ptr;
	ptr_array = *_ptr_array_ptr;
	while (*ptr_array)
	{
		ft_free(ptr_array);
		ptr_array++;
	}
	ft_free(_ptr_array_ptr);
}

void	dealloc_redirections(t_list *redir)
{
	t_list		*tmp;
	t_redirect	*curr;

	while (redir)
	{
		curr = redir->content;
		if (curr->file_path)
			ft_free(&curr->file_path);
		tmp = redir;
		redir = redir->next;
		ft_free(&tmp);
	}
}
