/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/13 22:50:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	if (argc == 1 && argv)
	{
		write(STDOUT_FILENO, SPLASH, 1368);
		ms = ft_calloc(1, sizeof(t_ms));
		if (init_start())
			return (1);
		if (init_ms(ms))
			return (msg_err("Failed to initialize ms.", 1));
		if (init_env(ms, envp))
			return (msg_err("Failed to initialize env.", 1));
		if (prompt(ms))
			return (msg_err("Something went wrong.", 1));
		free (ms->line);
		clean_tokenlist(&ms->tokens);
		clean_env(ms->env);
		free (ms);
		return (0);
	}
	return (msg_err("Please do not provide any arguments.", 1));
}

/*
builtins made:
- pwd(), saved as ms_pwd()

todo [short-term]
- find out how work with global variables without getting multiple def. error.
- get_env_key_idx(t_env **env, char *key) results in segfault if the key does not exist. Fix this. What is the desired behavior?
*/
