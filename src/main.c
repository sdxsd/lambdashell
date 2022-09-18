/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 18:56:53 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	if (argc == 1 && argv)
	{
		ms = ft_calloc(1, sizeof(t_ms));
		if (init_start())
			return (1);
		if (init_ms(ms))
			return (msg_err("init_ms()", FAILURE));
		if (init_env(ms, envp))
			return (msg_err("init_env()", FAILURE));
		if (prompt(ms))
		{
			free (ms->line);
			clean_tokenlist(&ms->tokenlist);
			clean_env(ms->env);
			free (ms);
			return (msg_err("Something went wrong.", 1));
		}
		free (ms->line);
		clean_tokenlist(&ms->tokenlist);
		clean_env(ms->env);
		free (ms);
		return (0);
	}
	return (msg_err("Please do not provide any arguments.", 1));
}
