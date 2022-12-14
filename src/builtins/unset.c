/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 17:15:47 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/09 17:15:47 by sbos          ########   odam.nl         */
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

int	string_cmp_fn(void *lst_content, void *needle)
{
<<<<<<< HEAD:src/dealloc/deallocate.c
	int	iter;

	if (data == NULL)
		return ;
	iter = 0;
	while (data[iter])
	{
		ft_free(&data[iter]);
		iter++;
	}
	ft_free(&data);
}

void	dealloc_lambda(t_shell *lambda)
{
	if (!lambda)
		return ;
	if (lambda->env)
		ft_lstclear(&lambda->env, dealloc_env_element);
	if (lambda->line)
		ft_free(&lambda->line);
	if (lambda->lines)
		dealloc_ptr_array((void **)lambda->lines);
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

void	dealloc_cmd(t_cmd *cmd)
{
	if (cmd->args)
		ft_lstclear(&cmd->args, free);
	if (cmd->path)
		ft_free(&cmd->path);
	if (cmd->redirections)
		dealloc_redirections(cmd->redirections);
}

void	dealloc_cmds(t_list *cmds)
{
	t_list	*tmp;
=======
	return (ft_strcmp(((t_env_element *)lst_content)->key, (char *)needle));
}

// TODO: Should anything special happen if no argument is provided?
int	unset(t_cmd *cmd, t_shell *lambda)
{
	char	**args;
>>>>>>> origin/master:src/builtins/unset.c

	args = cmd->args;
	while (*args)
	{
<<<<<<< HEAD:src/dealloc/deallocate.c
		dealloc_cmd(cmds->content);
		tmp = cmds;
		cmds = cmds->next;;
		ft_free(&tmp);
=======
		ft_lst_remove_if(&lambda->env, *args, string_cmp_fn);
		args++;
>>>>>>> origin/master:src/builtins/unset.c
	}
	return (SUCCESS);
}
