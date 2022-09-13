/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/12 15:01:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	ms = ft_calloc(1, sizeof(t_ms));
	if (init_start())
		return (1);
	if (init_ms(ms))
		return (msg_err("init_ms()", FAILURE));
	if (init_env(ms, envp))
		return (msg_err("init_env()", FAILURE));
	if (prompt(ms))
	{
		clean_env(ms->env);
		free (ms->line);
		free (ms->tokens);
		free (ms);
		return (1);
	}

	free (ms->line);
	clean_tokenlist(&ms->tokens);
	clean_env(ms->env);
	free (ms);

	(void)argc;
	(void)argv;
	return 0;
}

/*
builtins made:
- pwd(), saved as ms_pwd()

todo [short-term]
- find out how work with global variables without getting multiple def. error.
- get_env_key_idx(t_env **env, char *key) results in segfault if the key does not exist. Fix this. What is the desired behavior?
*/
