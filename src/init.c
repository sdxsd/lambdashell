/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:24:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/25 14:02:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_ms(t_ms *ms)
{
	ms = ft_calloc(1, sizeof(t_ms));
	if (!ms)
	{
		printf("Error: Mem allocation for ms struct failed.\n");
		return (1);
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
	{
		printf("Error: Mem allocation for environment failed.\n");
		return (1);
	}
	(void)envp;
	return (0); 
}

int	duplicate_env(char **target, char **source)
{
	int	i;

	i = 0;
	while (source[i])
	{
		target[i] = ft_strdup(source[i]);
		if (!target[i])
			return (1);
		i++;
	}
	return (0);
}



/*
env_write_entry(3)
Serves as a helper function for env_add_entry(3). It will add a new 
user-specified entry to env_global at the specified position.
*/

int	env_write_entry(t_ms *ms, int pos, char *entry)
{
	ms->env[pos] = ft_strdup(entry);
	if (!ms->env[pos])
		return (1);
	return (0);
}

/*
env_find_key(1)
Searches in env for the provided key. If found, it returns the position
of the key. Else, returns -1.
*/

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

/*
env_add_entry(2)
Adds an entry to env. It expects that the new entry is provided in 
key-value format. It uses env_find_key(2) to decide where to write the entry
in env. If env_find_key(2) could not find the key in env, it will
tell env_add_entry(3) to add the entry to the end of env. If the key
already exists in env, it will replace its corresponding value with
what is user-specified. It uses env_write_entry(3) for actually writing the 
entry.
*/

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
		return (1);
	if (init_ms(ms))
		return (1);
	if (init_env(ms, envp))
		return (1);
	if (duplicate_env(ms->env, envp))
		return (1);
	print_env(ms);

	// if (init_env(envp))
	// {
	// 	//free (env_global);
	// 	return (1);
	// }
	return (0);
}








// TODO: CLEANUP FUNCTION. CLEANUP OF ENV IS SHALLDOW, NEEDS FREE SUB STRINGS














/*
init()
- Checks whether the standard input file descriptor refers to a terminal.
- Calls init_env() to initialize our global variable env_global.
- TODO: Shorten by combining all if statements on single line
*/




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
