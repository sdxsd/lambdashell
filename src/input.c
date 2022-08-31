/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/30 11:47:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 11:57:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_last_char(char *line)
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
	if (*line && ft_strchr(charset, get_last_char(line)))
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

void	show_prompt(t_ms *ms)
{
	while (1)
	{
		ms->input_line = readline(">");
		if (ms->input_line)
		{
			parse_input(ms, ms->input_line);
		}
	}
	(void)ms;
}
