/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:19:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/13 22:53:20 by mikuiper      ########   odam.nl         */
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
	token_checker(ms->tokens);

	//dbg_print_tokens(&ms->tokens);
}

int	prompt(t_ms *ms)
{
	/*
	ms->line = ft_strdup("Hi, the shell you are using is < | $SHELL");
	line_parser(ms);
	*/
	///*
	while (1)
	{
		ms->line = readline("\033[;32mλ :: > \033[0;0m\2");
		if (ms->line == NULL)
			break ;
		if (ms->line[0] != 0)
		{
			add_history(ms->line);
			line_parser(ms);
			printf("%s\n", ms->line);
		}
	}
	//*/
	return (0);
}
