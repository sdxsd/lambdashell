/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:03:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 21:09:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(t_env **env)
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
			head = head->next;
			i++;
		}
		i++;
	}
	return (i);
}

// Note the -1 return value for errors
// This function assumes you have added indices using add_env_idx()
//add_env_idx(ms->env);
int	get_env_key_idx(t_env **env, char *key)
{
	t_env	*head;

	head = *env;
	
	if (!head)
		return (-1);
	else
	{
		while (head->next)
		{
			if (!ft_strncmp(head->key, key, ft_strlen(key)))
				return (head->idx);
			head = head->next;
		}
	}
	return (0);	
}

// returns value corresponding to key. Used together with get_env_key_idx()
char	*get_env_val(t_env **env, char *key)
{
	t_env	*head;

	head = *env;
	
	if (!head)
		return (NULL);
	else
	{
		while (head->next)
		{
			if (head->idx == get_env_key_idx(env, key))
				return (head->val);
			head = head->next;
		}
	}
	return (NULL);	
}

int	add_env_idx(t_env **env)
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
			head->idx = i;
			head = head->next;
			i++;
		}
		i++;
		head->idx = i;
	}
	return (0);
}

int	add_new_entry(t_ms *ms, t_env *node)
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
		*ms->env = node;
	return (0);
}

int	env_copier(t_ms *ms, char *line)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (1);
	node->key = ft_substr(line, 0, ft_strchr(line, '=') - line);
	if (!node->key)
		return (1);
	node->val = NULL;
	if (ft_strchr(line, '='))
	{
		node->val = ft_strdup(&ft_strchr((line), '=')[1]); // Trick to remove the "=""
		if (node->val == NULL)
			return (1);
	}
	node->next = NULL;
	if (add_new_entry(ms, node))
		return (1);
	return (0);
}
