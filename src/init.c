/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:24:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/25 15:28:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_ms(t_ms *ms)
{
	ms = ft_calloc(1, sizeof(t_ms));
	if (!ms)
	{
		return (msg_err("Mem allocation for ms struct failed.", 1));
	}
	return (0);
}

int	init_env(t_ms *ms, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	ms->env = ft_calloc((i + 1), (sizeof(char *)));
	if (!ms->env)
		return (msg_err("Mem allocation for environment failed.", 1));
	i = 0;
	while (envp[i])
	{
		ms->env[i] = ft_strdup(envp[i]);
		if (!ms->env[i])
			return (1);
		i++;
	}
	return (0); 
}

int	env_write_entry(t_ms *ms, int pos, char *entry)
{
	ms->env[pos] = ft_strdup(entry);
	if (!ms->env[pos])
		return (1);
	return (0);
}

int	env_find_key(t_ms *ms, char *key)
{
	int		i;
	char	*key_tmp;

	i = 0;
	key_tmp = ms_strjoin(key, "", '=');
	if (!key_tmp)
		return (-1);
	while (ms->env[i])
	{
		if (substring_start(ms->env[i], key_tmp))
		{
			free (key_tmp);
			return (i);
		}
		i++;
	}
	free (key_tmp);
	return (-1);
}

int	env_add_entry(t_ms *ms, char *key, char *value)
{
	int		i;
	char	*entry;
	
	i = env_find_key(ms, key);
	entry = ms_strjoin(key, value, '=');
	if (entry == NULL)
	{
		return (1);
	}
	if (i != -1)
	{
		free (ms->env[i]);
		env_write_entry(ms, i, entry);
	}
	else
	{
		i = 0;
		while (ms->env[i])
			i++;
		env_write_entry(ms, i, entry);
	}
	free (entry);
	return (0);
}

int	init_wrapper(t_ms *ms, char **envp)
{
	if (!isatty(0))
		return(msg_err("Standard input fd does not refer to terminal.", 1));
	if (init_ms(ms))
		return(msg_err("Failed to initialize ms.", 1));
	if (init_env(ms, envp))
		return(msg_err("Failed to initialize env.", 1));
	return (0);
}
