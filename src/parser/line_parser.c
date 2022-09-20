/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/30 11:47:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/20 15:50:21 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	line_get_n_words(char *line)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 1;
	while (line[i])
	{
		if (line[i] && line[i] == '\'' && line[i + 1])
		{
			while (line[++i] && line[i] != '\'')
				continue ;
		}
		else if (line[i] == '\"' && line[i + 1])
		{
			while (line[++i] && line[i] != '\"')
				continue ;
		}
		else if (line[i] && line[i] == '|')
			words++;
		i++;
	}
	return (words);
}

size_t	line_get_line_len(char *line, size_t i)
{
	size_t	len;

	len = 0;
	while (line[i + len])
	{
		if ((line[i + len]) && (line[i + len] == '\'') && (line[len + 1]))
		{
			len++;
			while ((line[i + len]) && (line[i + len] != '\''))
				len++;
		}
		else if ((line[i + len] == '\"') && (line[len + 1]))
		{
			len++;
			while ((line[i + len]) && (line[i + len] != '\"'))
				len++;
		}
		else if ((line[i + len]) && line[i + len] == '|')
			return (len);
		len++;
	}
	return (len);
}

char	**line_split_line_helper(char **lines, char *line)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	n_words;

	i = 0;
	start = 0;
	n_words = line_get_n_words(line);
	printf("n_words: %ld\n\n", n_words);
	while (i < n_words)
	{
		j = 0;
		lines[i] = malloc(sizeof(char) * (line_get_line_len(line, start) + 1));
		if (!lines[i])
			return (0);
		while (line[start + j] && (j < line_get_line_len(line, start)))
		{
			lines[i][j] = line[start + j];
			j++;
		}
		lines[i][j] = '\0';
		start = start + line_get_line_len(line, start) + 1;
		i++;
	}
	lines[i] = NULL;
	return (lines);
}

char	**line_trim_lines(char **lines)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (lines[i])
	{
		tmp = lines[i];
		lines[i] = ft_strtrim(lines[i], " \t\v\r\n\f");
		free(tmp);
		i++;
	}
	return (lines);
}

char	**line_split_line(char *line)
{
	char	**lines;

	if (!line)
		return (0);
	lines = malloc ((line_get_n_words(line) + 1) * sizeof(char *));
	if (!lines)
		return (0);
	lines = line_split_line_helper(lines, line);
	if (!lines)
		return (0);
	return (lines);
}

int	line_parser(t_ms *ms)
{

	if (line_check_syntax(ms->line, "<>|"))
		return (1);

	/* Expand line */
	ms->line = line_expander(ms->line, ms->env);
	
	char	**lines;
	lines = line_split_line(ms->line);
	lines = line_trim_lines(lines);
	///*
	int i = 0;
	while (lines[i])
	{
		printf("[%d]lines:%s\n", i, lines[i]);
		printf("[%d]len:%ld\n", i, ft_strlen(lines[i]));
		i++;
	}
	//*/
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
