/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:19:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/14 13:44:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	line_parser(t_ms *ms)
{
	ms->line = line_expander(ms->line, ms->env);
	tokenizer(ms->line, &ms->tokens);
	
	// IMPORTANT: token list has bug where first node is null. Hence removal
	t_list *head;
	head = ms->tokens;
	ms->tokens = ms->tokens->next;
	free (head);

	ft_lstiter(ms->tokens, token_add_types);
	//token_checker(ms->tokens);

	//dbg_print_tokens(&ms->tokens);
}

int	prompt(t_ms *ms)
{
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
	return (0);
}
