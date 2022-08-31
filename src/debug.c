/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:38:27 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 20:14:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dbg_print_env(t_ms *ms)
{
	t_env *cur;
	cur = *ms->env;
	while (cur->next)
	{
		printf("%s%s\n", cur->key, cur->val);
		cur = cur->next;
	}
	printf("%s%s\n", cur->key, cur->val);
	return (1);
}

int	dbg_print_env_idx(t_ms *ms)
{
	t_env *cur;
	cur = *ms->env;
	while (cur->next)
	{
		printf("[%d] %s%s\n", cur->idx, cur->key, cur->val);
		cur = cur->next;
	}
	printf("[%d] %s%s\n", cur->idx, cur->key, cur->val);
	return (1);
}
