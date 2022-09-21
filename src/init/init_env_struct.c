/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env_struct.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 16:16:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/19 16:16:32 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_env_struct(t_ms *ms, char **envp)
{
	int	i;

	ms->env = ft_calloc(1, sizeof(t_env));
	ms->tokenlist = ft_calloc(1, sizeof(t_list));
	i = 0;
	while (envp[i])
	{
		if (env_var_cloner(ms, envp[i]))
			return (msg_err("env_var_cloner()", FAILURE));
		i++;
	}
	env_init_idx(ms->env);
	return (0);
}
