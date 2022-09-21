/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 22:25:48 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/19 14:57:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
[t_cmd object]->args
*/

void	builtin_unset(char **args, t_ms *ms)
{
	size_t	i;

	i = 1;
	while (args[i] != NULL)
	{
		env_del_var(ms->env, args[i]);
		i++;
	}
}
