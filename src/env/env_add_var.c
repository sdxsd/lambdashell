/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_add_var.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 15:02:14 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/19 15:03:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
env_create_var() can be used to create a new node for the env linked list.
Following the creation, it can be added to the linked list using 
env_add_var().
*/

t_env	*env_create_var(char *key, char *val)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
		return (NULL);
	node->val = ft_strdup(val);
	if (!node->val)
	{
		free (node->val);
		return (NULL);
	}
	node->idx = -1;
	node->next = NULL;
	return (node);
}

/*
env_add_var() adds a new node to the end of the env linked list. It is
repeatedly called by env_var_cloner(), which creates a new node for each 
system env line.
*/

int	env_add_var(t_ms *ms, t_env *node)
{
	t_env *cur;

	if (env_len(ms->env))
	{
		cur = *ms->env;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
	else
	{
		*ms->env = node;
	}
	return (0);
}
