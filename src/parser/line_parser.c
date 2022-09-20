/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/30 11:47:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/20 13:22:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	line_parser(t_ms *ms)
{

	if (line_check_syntax(ms->line, "<>|"))
		return (1);

	/* Expand line */
	ms->line = line_expander(ms->line, ms->env);
	

	/* Tokenize line */
	//tokens_populate_tokenlist(ms->line, &ms->tokenlist);
	
	/* IMPORTANT: Please keep the following 4 lines of code for now. First elem of list is NULL. */
	//t_list *head;
	//head = ms->tokenlist;
	//ms->tokenlist = ms->tokenlist->next;
	//free (head);

	/* Add labels to tokens */
	//tokens_add_types(ms->tokenlist);
	
	/* Check for valid token syntax */
	//tokens_check_syntax(ms->tokenlist);
	
	/* Demonstrate token blks */
	//t_list	*token_blks_list;
	//token_blks_list = make_token_blks_list(&ms->tokenlist);
	//debug_print_token_blks_list(token_blks_list);
	return (0);
}
