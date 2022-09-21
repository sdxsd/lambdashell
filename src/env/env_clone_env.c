/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_clone_env.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 15:04:09 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/19 15:07:42 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
env_var_cloner() can be used to clone the system env into memory. The new env
is represented in a linked list, where each node contains the data of a single
line of the system env. Each node separates the data from a system env line into
key and value pairs.
*/

int	env_var_cloner(t_ms *ms, char *line)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (1);
	node->key = ft_substr(line, 0, ft_strchr(line, '=') - line);
	if (!node->key)
	{
		return (1);
	}
	node->val = NULL;
	if (ft_strchr(line, '='))
	{
		node->val = ft_strdup(&ft_strchr((line), '=')[1]);
		if (node->val == NULL)
			return (1);
	}
	node->next = NULL;
	if (env_add_var(ms, node))
		return (1);
	return (0);
}
