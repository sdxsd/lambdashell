/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:38:27 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 17:45:55 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	debug_print_env(t_ms *ms)
{
	t_env *cur;
	cur = *ms->env;
	while (cur->next)
	{
		printf("%s=%s\n", cur->key, cur->val);
		cur = cur->next;
	}
	printf("%s=%s\n", cur->key, cur->val);
	return (1);
}

int	debug_print_env_keys(t_ms *ms)
{
	t_env *cur;
	cur = *ms->env;
	while (cur->next)
	{
		printf("%s\n", cur->key);
		cur = cur->next;
	}
	printf("%s\n", cur->key);
	return (1);
}

int	debug_print_env_idx(t_ms *ms)
{
	t_env *cur;
	cur = *ms->env;
	while (cur->next)
	{
		printf("[%d] %s=%s\n", cur->idx, cur->key, cur->val);
		cur = cur->next;
	}
	printf("[%d] %s=%s\n", cur->idx, cur->key, cur->val);
	return (1);
}
