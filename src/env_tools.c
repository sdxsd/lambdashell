/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:03:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/02 12:14:05 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get number of env variables
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

// find node position in env list of where the key node resides
// can also be used to find out whether key exists (-1 means not exist)
int	get_env_key_pos(t_env **env, char *key)
{
	t_env	*head;
	int		i;

	head = *env;
	i = 0;
	if (!head)
		return (-1);
	else
	{
		while (head->next)
		{
			if (!ft_strncmp(head->key, key, ft_strlen(key)))
				return (i);
			head = head->next;
			i++;
		}
	}
	return (-1);
}

// returns value corresponding to key. Used together with get_env_key_pos()
// get value of chosen env key
char	*get_env_val(t_env **env, char *key)
{
	t_env	*head;
	int	i;

	head = *env;
	i = 0;
	if (!head)
		return (NULL);
	else
	{
		while (head->next)
		{
			if (i == get_env_key_pos(env, key))
				return (head->val);
			head = head->next;
			i++;
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

int	add_env_entry(t_ms *ms, t_env *node)
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

int	env_entry_cloner(t_ms *ms, char *line)
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
	if (add_env_entry(ms, node))
		return (1);
	return (0);
}

int	env_edit_val(t_env **env, char *key, char *new_val)
{
	t_env	*head;
	int		i;

	head = *env;
	i = 0;
	if (!head)
		return (1);
	else
	{
		while (head->next)
		{
			if (!ft_strncmp(head->key, key, ft_strlen(key)))
			{
				free (head->val);
				head->val = ft_strdup(new_val);
				if (!head->val)
					return (1);
				return (0);
			}
			head = head->next;
			i++;
		}
	}
	return (1);
}

// free env node (free key and free val)
int	free_env_node(t_env *node)
{
	free (node->key);
	free (node->val);
	free (node);
	return (0);
}


void env_del_key_val(t_env **head, char *key)
{
	t_env *tmp1;
	t_env *tmp2;
	
	
	if(!ft_strncmp((*head)->key, key, ft_strlen(key)))
	{
		tmp1 = *head;
		*head = (*head)->next;
		free_env_node(tmp1);
	}
	else
	{
		t_env *current  = *head;
		while(current->next != NULL)
		{
			tmp1 = current->next;
			if(!ft_strncmp((*head)->key, key, ft_strlen(key)))
			{
				tmp2 = tmp1->next;
				current->next = tmp2;
				free_env_node(tmp1);
				break;
			}
			else
				current = current->next;
		}
	}
}

// TODO: ADD NEW ENV ENTRY. MAKE SURE TO CHECK WHETHER KEY ALREADY EXISTS USING GET_ENV_KEY_POS()
// TODO: DELETE KEY FROM ENV LIST