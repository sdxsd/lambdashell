/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:19:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 13:28:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	prompt(t_ms *ms)
{
	clear_screen();
	splash();
	
	ms->line = ft_strdup("Good evening $USER | Do you want your Ferrari | | keys? | Blabla");
	printf("Minishell is currently parsing:\n%s\n\n", ms->line);
	line_parser(ms);
	//dbg_print_env(ms);
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
	return (0);
}
