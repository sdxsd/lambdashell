/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:03:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 20:39:02 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_len(t_env **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = *env;
	
	if (!head)
		return (0);
	else
	{
		while (head->next)
		{
			i++;
			head = head->next;
		}
		i++;
	}
	return (i);
}

int	add_idx_env(t_env **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = *env;
	if (!head)
		return (1);
	else
	{
		while (head->next)
		{
			i++;
			head->idx = i;
			head = head->next;
		}
		i++;
		head->idx = i;
	}
	return (0);
}

int	add_new_entry(t_ms *ms, t_env *new_node)
{
	t_env *cur;

	if (get_env_len(ms->env))
	{
		cur = *ms->env;
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
	else
		*ms->env = new_node;
	return (0);
}

int	env_copier(t_ms *ms, char *line)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->key = ft_substr(line, 0, ft_strchr(line, '=') - line);
	if (!new_node->key)
		return (1);
	new_node->val = NULL;
	if (ft_strchr(line, '='))
	{
		new_node->val = ft_strdup(ft_strchr(line, '='));
		if (new_node->val == NULL)
			return (1);
	}
	new_node->next = NULL;
	if (add_new_entry(ms, new_node))
		return (1);
	return (0);
}
