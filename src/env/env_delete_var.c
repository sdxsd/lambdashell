/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_delete_var.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 14:59:07 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/19 15:11:35 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
free_env_var() frees the memory that was allocated per environment node.
It is used by env_del_var_helper().
*/

int	free_env_var(t_env *node)
{
	free (node->key);
	free (node->val);
	free (node);
	return (0);
}

/*
env_del_var_helper() is a helper function used by env_del_var().
It merely exists to make env_del_var() comply with the 42 norme.
*/

 int	env_del_var_helper(t_env **head, char *key)
{
	t_env *current;
	t_env *next_node;
	t_env *next_next_node;

	current = *head;
	while(current->next != NULL)
	{
		next_node = current->next;
		if(next_node->idx == env_get_var_key_idx(head, key))
		{
			next_next_node = next_node->next;
			current->next = next_next_node;
			free_env_var(next_node);
			return (0);
		}
		else
			current = current->next;
	}
	return (0);
}

/*
env_del_var() allows for the deletion of an environment entry by providing
the entry's corresponding key. If the key does not exist it returns 1, else 0.
*/

int	env_del_var(t_env **env, char *key)
{
	t_env *next_node;
	
	if (env_get_var_key_idx(env, key) == -1)
		return (1);
	if((*env)->idx == env_get_var_key_idx(env, key))
	{
		next_node = *env;
		*env = (*env)->next;
		free_env_var(next_node);
	}
	else
		env_del_var_helper(env, key);
	return (0);
}
