/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:19:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/17 22:59:49 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_screen(void)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
}

void	line_parser(t_ms *ms)
{
	/* Expand line */
	ms->line = line_expander(ms->line, ms->env);

	/* Tokenize line */
	tokenizer(ms->line, &ms->tokens);
	
	/* IMPORTANT: Please keep the following 4 lines of code for now. First elem of list is NULL. */
	t_list *head;
	head = ms->tokens;
	ms->tokens = ms->tokens->next;
	free (head);

	/* Add labels to tokens */
	ft_lstiter(ms->tokens, token_add_types);

	/* Check for valid token syntax */
	token_checker(ms->tokens);
	
	/* Demonstrate the creation of token blocks */
	t_list	*token_block_list;
	token_block_list = make_token_block_list(&ms->tokens);
	dbg_print_token_block_list(token_block_list);
}

int	prompt(t_ms *ms)
{
	clear_screen();
	splash();
	
	ms->line = ft_strdup("Good evening $USER | Do you want your Ferrari keys? | Blabla");
	//printf("Minishell is currently parsing:\n%s\n\n", ms->line);
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
