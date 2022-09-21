/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_tools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 15:10:00 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/19 15:10:02 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
env_len() returns the number of nodes in the env linked list.
*/

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

/*
env_get_var_key_idx() returns the index value of a desired key in the env linked
list. If the key does not exist, or if no linked list is provided, it returns -1.
*/

int	env_get_var_key_idx(t_env **env, char *key)
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
			if (ft_strlen(head->key) == ft_strlen(key))
				if (!ft_strncmp(head->key, key, ft_strlen(head->key)))
					return (head->idx);
			head = head->next;
			i++;
		}
	}
	return (-1);
}

/*
env_get_val() returns the value corresponding to a desired key in the env linked
list. If the key does not exist, or if no linked list is provided, it returns
NULL.
*/

char	*env_get_val(t_env **env, char *key)
{
	t_env	*head;
	int	i;

	if (strlen(key) == 0)
		return ("");
	head = *env;
	i = 0;
	if (!head || env_get_var_key_idx(env, key) == -1)
		return (NULL);
	else
	{
		while (head->next)
		{
			if (i == env_get_var_key_idx(env, key))
				return (head->val);
			head = head->next;
			i++;
		}
	}
	return (head->val);
	//return (NULL);
}

/*
env_init_idx() is used to assign index values to each node in the env linked
list.
*/

int	env_init_idx(t_env **env)
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

/*
env_edit_var_val() allows for changing the value of a particular key in your env.
It does this by searching for the key in the linked list env, starting at the
head. Note: This function assumes that your env has no duplicate keys. If a
duplicate key exists, this function will only update the value of the first 
occurring key.
*/

int	env_edit_var_val(t_env **env, char *key, char *new_val)
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
