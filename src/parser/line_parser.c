/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/30 11:47:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/21 11:33:52 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	line_parser(t_ms *ms)
{

	// Check line syntax
	if (line_check_syntax(ms->line, "<>|"))
		return (1);

	// Expand line
	ms->line = line_expander(ms->line, ms->env);
	
	// Remove quotes from line
	// TODO!

	printf("%s\n", ms->line);
	//char	**lines;
	ms->lines = line_split_line(ms->line);
	ms->lines = line_trim_lines(ms->lines);
	///*
	//int i = 0;
	//while (ms->lines[i])
	//{
	//	printf("[%d]ms->lines:%s\n", i, ms->lines[i]);
	//	printf("[%d]len:%ld\n", i, ft_strlen(ms->lines[i]));
	//	i++;
	//}
	return (0);
}



	//
	/* Tokenize line */
	//tokens_populate_tokenlist(lines, &ms->tokenlist);
	
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