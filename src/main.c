/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/09 13:57:58 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;
	ms = ft_calloc(1 + 1, sizeof(t_ms));
	if (init_start())
		return (1);
	if (init_ms(ms))
		return (msg_err("Failed to initialize ms.", 1));
	if (init_env(ms, envp))
		return (msg_err("Failed to initialize env.", 1));
	// printf("pannekoek value: %s\n", get_env_val(ms->env, ""));
	if (prompt(ms))
		return (1);
	//printf("End of main()");
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
