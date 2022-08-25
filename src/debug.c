/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:38:27 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/25 14:38:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dbg_print_env(t_ms *ms)
{
	int	i;

	i = 0;
	if (!ms->env)
		return (1);
	while (ms->env[i])
	{
		printf("%s\n", ms->env[i]);
		i++;
	}
	return (0);
}
