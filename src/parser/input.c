/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/30 11:47:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 13:28:58 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_quotations(char *line)
{
	int	quote;
	int	squote;

	quote = 0;
	squote = 0;
	while (*line)
	{
		if (*line == '\'' && squote == 0)
			squote = 1;
		else if (*line == '\'' && squote == 1)
			squote = 0;
		if (*line == '"' && quote == 0)
			quote = 1;
		else if (*line == '"' && quote == 1)
			quote = 0;
		line++;
	}
	if (quote || squote)
	{
		printf("Error. Your line has an unclosed quotation mark.\n");
		return (1);
	}
	return (0);
}

int	check_first_char(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '|')
	{
		printf("Error. Found forbidden token at start of line.\n");
		return (1);
	}
	return (0);
}

int	last_char(char *line)
{
	char	last_char;
	while (*line)
	{
		if (*line != ' ')
			last_char = *line;
		line++;
	}
	return (last_char);
}

int check_last_char(char *line, char *charset)
{
	if (*line && ft_strchr(charset, last_char(line)))
	{
		printf("Error. Found forbidden token at end of line.\n");
		return (1);
	}
	return (0);
}

// very simple to get started, requires more checks
int	check_line_formatting(char *line, char *charset)
{
	if (check_first_char(line))
		return (1);
	if (check_last_char(line, charset))
		return (1);
	if (check_quotations(line))
		return (1);
	return (0);
}

int	parse_input(t_ms *ms, char *line)
{
	char	*tmp;

	if (check_line_formatting(line, "<>|"))
		return (1);
	(void)tmp;
	(void)ms;
	return (0);
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

	token_add_types(ms->tokens);
	dbg_print_tokens(&ms->tokens);

	//ft_lstiter(ms->tokens, token_add_types);

	/* Check for valid token syntax */
	token_checker(ms->tokens);
	
	/* Demonstrate the creation of token blocks */
	//t_list	*token_block_list;
	//token_block_list = make_token_block_list(&ms->tokens);
	//dbg_print_token_block_list(token_block_list);
}
