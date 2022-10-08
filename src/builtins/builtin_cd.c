/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 21:59:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/08 20:37:09 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
builtin_cd() uses a t_cmd object.
The t_cmd object's args is used in builtin_cd().

pipe_blk_alloc() creates a t_pipe_blk object.
This object has two t_cmd objects via cmd_constructor()

So to run builtin_cd you need to run pipe_blk_alloc() first.

exec_list_generator() -> new_exec_element() + assign_exec_element() -> cmd_constructor()
*/

int	builtin_cd(t_cmd *cmd_object, t_ms *ms)
{
	if (ft_get_n_strings(cmd_object->args) > 2)
	{
		printf("Error1. Too many args\n");
		return (1);
	}
	if (ft_strncmp(cmd_object->args[0], "cd", ft_strlen("cd")) != 0)
	{
		printf("Error2!\n");
		return (1);
	}
	if (!cmd_object->args[1])
	{
		if (chdir(env_get_val(ms->env, "HOME")))
		{
			printf("Error3!\n");
			return (1);
		}
		return (0);
	}
	if (chdir(cmd_object->args[1]))
	{
		printf("Error4!\n");
		return (1);
	}
	return (0);
}

// Use this version of builtin_cd() to quickly test whether it works.
// Instead of processing a t_cmd object, it simply processes a char **, which
// can be easily created in main.c using ft_split().
// Try out cmd_strings = ft_split("cd /home/mkuipers/Desktop", ' ');
// Try out cmd_strings = ft_split("cd", ' ');
/*

int	builtin_cd2(char **cmd_strings, t_ms *ms)
{
	if (ft_get_n_strings(cmd_strings) > 2)
	{
		printf("Error1. Too many args\n");
		return (1);
	}
	if (ft_strncmp(cmd_strings[0], "cd", ft_strlen(cmd_strings[0])) != 0)
	{
		printf("Error2!\n");
		return (1);
	}
	if (!cmd_strings[1])
	{
		if (chdir(env_get_val(ms->env, "HOME")))
		{
			printf("Error3!\n");
			return (1);
		}
		return (0);
	}
	if (chdir(cmd_strings[1]))
	{
		printf("Error4!\n");
		return (1);
	}
	return (0);
}
*/