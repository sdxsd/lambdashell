/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/25 15:32:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;
	ms = ft_calloc(1 + 1, sizeof(t_ms));

	if (init_wrapper(ms, envp))
		return (1);
	env_add_entry(ms, "SHELL", "42");
	env_add_entry(ms, "Thiswillbeaddedtothebottom", "See?");
	dbg_print_env(ms);
	//clean_ms_wrapper(ms);
	(void)argc;
	(void)argv;
	return 0;
}
