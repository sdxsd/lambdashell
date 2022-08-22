/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:24:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/22 17:06:20 by mikuiper      ########   odam.nl         */
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
get_shell_lvl()
-
-
*/

/*
int	get_shell_lvl(char **envp)
{

}
*/

/*
env_add_keyvalue()
Adds new entry to the global variable env_global. It expects that the new
entry is provided in key-value format. If the key already exists in env_global,
it will replace its corresponding value with what is user-specified.
*/


int	env_add_keyvalue(char *key, char *value)
{
	int		i;
	char	*key_tmp;
	char	*key_value;
	int		env_i;
	
	env_i = env_find_key(key);
	i = 0;
	key_tmp = ft_strjoin(key, "=");
	if (!key_tmp)
		return (1);
	key_value = ft_strjoin(key_tmp, value);
	if (!key_value)
	{
		free (key_tmp);
		return (1);
	}
	if (env_i == -1)
	{
		while (env_global[i])
			i++;
		i++;
		if (!value)
			env_global[env_i] = key_tmp;
		else
			env_global[env_i] = key_value;
	}
	else
	{
		free (env_global[env_i]);
		if (!value)
			env_global[env_i] = key_tmp;
		else
			env_global[env_i] = key_value;
	}
	free (key_tmp);
	return (0);
}

int	env_find_key(char *key)
{
	int		i;
	char	*key_tmp;

	i = 0;
	key_tmp = ft_strjoin(key, "=");
	if (!key_tmp)
		return (0); // error trigger
	while (env_global[i])
	{
		if (substring_start(env_global[i], key_tmp))
			return (i);
		i++;
	}
	free (key_tmp);
	return (-1);
}
