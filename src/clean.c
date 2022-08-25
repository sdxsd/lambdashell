/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 13:57:16 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/25 15:23:11 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	clean_ms_env(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->env[i])
	{
		free (ms->env[i]);
		i++;
		ms->env[i] = NULL;
	}
	free (ms->env);
	ms->env = NULL;
	return (0);
}

int	clean_ms_wrapper(t_ms *ms)
{
	if (!ms)
		return (1);
	clean_ms_env(ms);
	free (ms);
	ms = NULL;
	return (0);
}
