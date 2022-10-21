/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/08 20:35:50 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	prompt(t_ms *ms)
{
	t_exec_element *exec_list;

	ms->line = readline("λ :: > ");
	if (ft_strlen(ms->line) < 1)
		return (SUCCESS);
	line_parser(ms);
	exec_list = tokenizer(ms);
	exec_list_generator(exec_list, ms->env);
	dbg_print_exec_list(exec_list);
	executor(exec_list);
	free(ms->line);
	dealloc_exec_list(exec_list);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	splash();
	if (argc == 1 && argv)
	{
		if (check_fd())
			return (msg_err("main()", FAILURE));
		ms = ft_calloc(1, sizeof(t_ms));
		if (!ms)
			return (msg_err("main()", FAILURE));
		if (init_ms_struct(ms))
			return (msg_err("main()", FAILURE));
		if (init_env_struct(ms, envp))
			return (msg_err("main()", FAILURE));
		while (TRUE)
		{
			prompt(ms);
		}
	}
	return (FAILURE);
}
