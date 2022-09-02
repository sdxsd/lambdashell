/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:24:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/02 15:42:31 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO!
int	init_ms(t_ms *ms)
{
	ms->input_line = NULL;
	ms->cmd = NULL;
	return (0);
}

int	init_env(t_ms *ms, char **envp)
{
	int	i;

	ms->env = ft_calloc(1, sizeof(t_env));
	i = 0;
	while (envp[i])
	{
		if (env_entry_cloner(ms, envp[i]))
			return (msg_err("Failed to duplicate env.", 1));
		i++;
	}
	init_env_idx(ms->env);
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
