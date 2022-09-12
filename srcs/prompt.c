/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:19:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/12 14:45:42 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_parser(t_ms *ms)
{
	if (check_line_formatting(ms->line, "|<>"))
		return (1);
	ms->line = line_expander(ms->line, ms->env);
	if (!ms->line)
		return (1);
	if (line_tokenizer(ms->line, &ms->tokens))
		return (1);
	if (check_token_formatting(&ms->tokens))
		return (1);
	
	// IMPORTANT: token list has bug where first node is null, hence its removal.
	t_list *head;
	head = ms->tokens;
	ms->tokens = ms->tokens->next;
	free (head);

	// Add types to tokens
	ft_lstiter(ms->tokens, token_add_types);

	// Print entire token list (values + types)
	dbg_print_tokens(&ms->tokens);
	return (0);
}

int	prompt(t_ms *ms)
{
	ms->line = ft_strdup("You use $SHELL and your home is at $HOME");
	if (line_parser(ms))
		return (1);
	/*
	while (1)
	{
		ms->line = readline("\033[;32m$> \033[0;0m\2");
		if (ms->line == NULL)
			break ;
		if (ms->line[0] != 0)
		{
			add_history(ms->line);
			line_parser(ms);
		}
	}
	*/
	return (0);
}
