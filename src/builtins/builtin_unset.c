/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 22:25:48 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 12:20:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
[t_cmd object]->args
*/

void	builtin_unset(t_ms *ms, char **args)
{
	size_t	i;

	i = 1;
	while (args[i] != NULL)
	{
		env_del_var(ms->env, args[i]);
		i++;
	}
}
