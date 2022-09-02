/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/02 16:30:22 by mikuiper      ########   odam.nl         */
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
	//show_prompt(ms);
	//env_edit_val(ms->env, "SHELL", "JohnnyBravo");
	env_del_entry(ms->env, "SHLVL");
	//env_del_entry(ms->env, "TERM");
	dbg_print_env(ms);

	//printf("%s", get_env_val(ms->env, "SHELL"));
	(void)argc;
	(void)argv;
	return 0;
}


// builtins made
//ms_pwd();

// todo: be able to delete key-value
// todo: change value of key