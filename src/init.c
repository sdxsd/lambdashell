/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:24:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/26 15:42:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_ms(t_ms *ms)
{
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



//increment_shlvl