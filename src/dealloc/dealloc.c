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

int	dealloc_cmd(void *cmd_ptr)
{
	t_cmd	**_cmd_ptr;
	t_cmd	*cmd;

	_cmd_ptr = cmd_ptr;
	cmd = *_cmd_ptr;
	dealloc_ptr_array(&cmd->args);
	ft_free(&cmd->path);
	dealloc_lst(&cmd->redirections, dealloc_redirection);
	ft_free(_cmd_ptr);
	return (FAILURE);
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

int	dealloc_token(void *token_ptr)
{
	t_token	**_token_ptr;
	t_token	*token;

	_token_ptr = token_ptr;
	token = *_token_ptr;
	ft_free(&token->content);
	ft_free(_token_ptr);
	return (FAILURE);
}

int	dealloc_lambda(t_shell *lambda)
{
	dealloc_lst(&lambda->tokens, dealloc_token);
	dealloc_lst(&lambda->env, dealloc_env_element);
	dealloc_lst(&lambda->cmds, dealloc_cmd);
	ft_free(&lambda->line);
	ft_free(&lambda->cwd);
	return (FAILURE);
}

void	dealloc_ptr_array(void *ptr_array_ptr)
{
	void	***_ptr_array_ptr;
	void	**ptr_array;

	_ptr_array_ptr = ptr_array_ptr;
	ptr_array = *_ptr_array_ptr;
	if (ptr_array)
	{
		while (*ptr_array)
		{
			ft_free(ptr_array);
			ptr_array++;
		}
	}
	ft_free(_ptr_array_ptr);
}

int	dealloc_redirection(void *redirect_ptr)
{
	t_redirect	**_redirect_ptr;
	t_redirect	*redirect;

	_redirect_ptr = redirect_ptr;
	redirect = *_redirect_ptr;
	ft_free(&redirect->file_path);
	ft_free(_redirect_ptr);
	return (FAILURE);
}
