/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:24:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/22 12:25:03 by mikuiper      ########   odam.nl         */
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
