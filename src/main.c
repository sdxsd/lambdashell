/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/20 21:21:15 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	prompt(t_ms *ms)
{
	splash();
	ms->line = ft_strdup("Good evening $USER | Do you want your 'Ferrari | Blabla'");
	printf("Minishell is currently parsing:\n%s\n\n", ms->line);
	line_parser(ms);
	/*
	t_cmd	*cmd;
	ms->line = ft_strdup("Hi, the shell you are using is < | $SHELL");
	line_parser(ms);
	(void)cmd;
	cmd = cmd_constructor("nano", ms->env);
	if (!cmd)
		return (FAILURE);
	execute_command(cmd);
	*/
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	if (argc == 1 && argv)
	{
		//global_sig = 0;
		if (check_fd())
			return (msg_err("fd problem()", FAILURE));
		ms = ft_calloc(1, sizeof(t_ms));
		if (!ms)
			return (1);
		if (init_ms_struct(ms))
			return (msg_err("init_ms_struct()", FAILURE));
		if (init_env_struct(ms, envp))
			return (msg_err("init_env_struct()", FAILURE));
		prompt(ms);
		//free (ms->line);
		//clean_tokenlist(&ms->tokenlist);
		//clean_env(ms->env);
		//free (ms);
		return (0);
	}
	return (msg_err("Please do not provide any arguments.", 1));
}

/*
while (TRUE)
{
	color_orange();
	printf("λ :: > ");
	color_reset();
	ms->line = readline("");
	if (ms->line == NULL)
		break ;
	if (ms->line[0] != 0)
	{
		add_history(ms->line);
		line_parser(ms);
		printf("result: %s\n", ms->line);
	}
}
*/