/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:24:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/22 22:22:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
init_global()
- Allocates memory for global variable env_global.
- Copies
- TODO: Cleanup if ft_strdup() fails.
*/

int     init_global(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env_global = ft_calloc((i + 1), (sizeof(char *)));
	if (!env_global)
	{
		printf("Error: Mem allocation for env_global. failed.\n");
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		env_global[i] = ft_strdup(envp[i]);
		if (!env_global[i])
			return (1);
		i++;
	}
	return (0);
}

/*
init()
- Checks whether the standard input file descriptor refers to a terminal.
- Calls init_global() to initialize our global variable env_global.
- TODO: Shorten by combining all if statements on single line
*/

int	init(char **envp)
{
	if (!isatty(0))
		return (1);
	if (init_global(envp))
	{
		free (env_global);
		return (1);
	}
	return (0);
}

/*
env_add_entry(2)
Adds an entry to env_global. It expects that the new entry is provided in 
key-value format. It uses env_find_key(1) to decide where to write the entry
in env_global. If env_find_key(1) could not find the key in env_global, it will
tell env_add_entry(2) to add the entry to the end of env_global. If the key
already exists in env_global, it will replace its corresponding value with
what is user-specified. It uses env_write_entry(3) for actually writing the 
entry.
*/

int	env_add_entry(char *key, char *value)
{
	int		i;
	char	*entry;
	
	i = env_find_key(key);
	entry = ms_strjoin(key, value, '=');
	if (entry == NULL)
	{
		return (1);
	}
	if (i != -1)
	{
		free (env_global[i]);
		env_write_entry(i, entry, value);
	}
	else
	{
		i = 0;
		while (env_global[i])
			i++;
		env_write_entry(i, entry, value);
	}
	free (entry);
	return (0);
}

/*
env_write_entry(3)
Serves as a helper function for env_add_entry(2). It will add a new 
user-specified entry to env_global at the specified position.
*/

int	env_write_entry(int pos, char *entry, char *value)
{
	env_global[pos] = ft_strdup(entry);
	if (!env_global[pos])
		return (1);
	return (0);
}

/*
env_find_key(1)
Searches in env_global for the provided key. If found, it returns the position
of the key. Else, returns -1.
*/

int	env_find_key(char *key)
{
	int		i;
	char	*key_tmp;

	i = 0;
	key_tmp = ms_strjoin(key, "", '=');
	if (!key_tmp)
		return (-1);
	while (env_global[i])
	{
		if (substring_start(env_global[i], key_tmp))
		{
			free (key_tmp);
			return (i);
		}
		i++;
	}
	free (key_tmp);
	return (-1);
}

/*
get_shell_lvl()
-
-
*/

/*
int	get_shell_lvl(char **envp)
{

}
*/