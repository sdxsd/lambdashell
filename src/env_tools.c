/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:03:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/02 16:38:17 by mikuiper      ########   odam.nl         */
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

int	get_env_key_idx(t_env **env, char *key)
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
				return (head->idx);
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

int	init_env_idx(t_env **env)
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

/*
env_edit_val() allows for changes the value corresponding to a particular
key in your environment. It does this by searching for the key in the linked
list environment, starting at the head. Note: This function assumes that your 
environment has no duplicate keys. If a duplicate key exists, this function will
only update the value of the first occurring key.
*/

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

/*
free_env_node() frees the memory that was allocated per environment node.
It is used by env_del_entry_helper().
*/

int	free_env_node(t_env *node)
{
	free (node->key);
	free (node->val);
	free (node);
	return (0);
}

/*
env_del_entry_helper() is a helper function used by env_del_entry().
It merely exists to make env_del_entry() comply with the 42 norme.
*/

static int	env_del_entry_helper(t_env **head, char *key)
{
	t_env *current;
	t_env *next_node;
	t_env *next_next_node;

	current = *head;
	while(current->next != NULL)
	{
		next_node = current->next;
		if(next_node->idx == get_env_key_idx(head, key))
		{
			next_next_node = next_node->next;
			current->next = next_next_node;
			free_env_node(next_node);
			return (0);
		}
		else
			current = current->next;
	}
	return (0);
}

/*
env_del_entry() allows for the deletion of an environment entry by providing
the entry's corresponding key. If the key does not exist it returns 1, else 0.
*/

int	env_del_entry(t_env **env, char *key)
{
	t_env *current;
	t_env *next_node;
	
	if (get_env_key_idx(env, key) == -1)
		return (1);
	current = *env;
	if((*env)->idx == get_env_key_idx(env, key))
	{
		next_node = *env;
		*env = (*env)->next;
		free_env_node(next_node);
	}
	else
		env_del_entry_helper(env, key);
	return (0);
}


// TODO: ADD NEW ENV ENTRY. MAKE SURE TO CHECK WHETHER KEY ALREADY EXISTS USING GET_ENV_KEY_POS()