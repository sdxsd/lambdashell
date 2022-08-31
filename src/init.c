/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:24:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 18:22:09 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO!
int	init_ms(t_ms *ms)
{
	ms->input_line = NULL;
	ms->cmd = NULL;
	ms->env_len = 0;
	return (0);
}

int	add_new_entry(t_ms *ms, t_env *new_node)
{
	t_env *cur;
	if (ms->env_len)
	{
		cur = *ms->env;
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
	else
		*ms->env = new_node;
	ms->env_len++;
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

int	init_env(t_ms *ms, char **envp)
{
	int	i;

	//ms->env = NULL;
	ms->env = ft_calloc(1, sizeof(t_env));
	i = 0;
	while (envp[i])
	{
		if (env_copier(ms, envp[i]))
			return (msg_err("Failed to duplicate env.", 1));
		i++;
	}
	return (0);
}

int	init_start(void)
{
	if (!isatty(0))
		return(msg_err("Standard input fd does not refer to terminal.", 1));
	if (!isatty(1))
		return(msg_err("Standard output fd does not refer to terminal.", 1));
	if (!isatty(2))
		return(msg_err("Standard error fd does not refer to terminal.", 1));
	global_sig = 0;
	return (0);
}
