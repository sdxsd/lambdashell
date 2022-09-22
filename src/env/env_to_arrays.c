/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_to_arrays.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 16:22:08 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 18:34:08 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// NOTE: Takes an t_env double pointer and returns
// the shell environment in form of string array.
// Used in cmd_constructor() to provide the shell env in
// the correct format for execve()
char	**env_to_arrays(t_env **env)
{
	char	**envp;
	t_env	*env_element;
	int		iter;
	int		len;

	iter = 0;
	len = env_len(env);
	envp = malloc(sizeof(char *) * len);
	env_element = *env;
	if (!envp)
	{
		msg_err("env_to_arrays()", FAILURE);
		return (NULL);
	}
	while (iter < len)
	{
		envp[iter] = env_element->val;
		env_element = env_element->next;
		iter++;
	}
	return (envp);
}

char	**env_vals_to_arrays(t_env **env)
{
	char	**envp;
	t_env	*env_element;
	int		iter;
	int		len;

	iter = 0;
	len = env_len(env);
	envp = malloc(sizeof(char *) * len);
	env_element = *env;
	if (!envp)
	{
		msg_err("env_to_arrays()", FAILURE);
		return (NULL);
	}
	while (iter < len)
	{
		envp[iter] = env_element->val;
		env_element = env_element->next;
		iter++;
	}
	return (envp);
}

char	**env_entries_to_arrays(t_env **env)
{
	char	**envp;
	t_env	*env_element;
	int		iter;
	char *tmp1;

	iter = 0;
	envp = malloc(sizeof(char *) * (env_len(env) + 1));
	env_element = *env;
	if (!envp)
	{
		msg_err("env_to_arrays()", FAILURE);
		return (NULL);
	}
	while (iter < env_len(env))
	{
		tmp1 = ft_glue_strings(env_element->key, env_element->val, '=');
		envp[iter] = tmp1;
		env_element = env_element->next;
		iter++;
	}
	envp[iter] = NULL;
	return (envp);
}
