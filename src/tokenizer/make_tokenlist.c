/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_tokenlist.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 13:32:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 13:37:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
tokenizer() scans the input line and isolates every word and turns it into a
"token", which will be chained together in a linked list. Here, each node
contains a "value" variable (i.e. the char array for the isolated word), and a
"type" variable, describing the category to which the token belongs (e.g. 
string, write operator, read operator, etc.)

IMPORTANT: The function below is not finished. Text between single quotes
should not be divided into separate tokens. 
*/

int	tokenizer(char *line, t_list **tokens)
{
	size_t	i;
	char	*token;
	int		len;

	i = 0;
	len = 0;
	while (i < ft_strlen(line))
	{
		while (ft_ischarset(line[i], " $\t\v\r\n\f"))
			i++;
		len = ft_strpos_charset(&line[i], " $\t\v\r\n\f");
		token = ft_substr(line, i, len);
		if (ft_strlen(token) == 0)
			return (1);
		token_make_and_add(token, tokens);
		i = i + len;
	}
	return (0);
}

int	token_chunk_size(t_list *tokenlist)
{
	size_t	size;

	size = 0;
	t_token	*current;

	if (((t_token *)tokenlist->content)->type == tkn_pipe)
		tokenlist = tokenlist->next;
	if (tokenlist->next == NULL)
		return (1);
	while (tokenlist)
	{
		current = tokenlist->content;
		if (current->type == tkn_pipe)
			return (size);
		size++;
		tokenlist = tokenlist->next;
	}
	return (size);
}

int	make_and_add_token_block(t_list **pipe_block_list, char **token_array)
{
	t_pipe_blk	*pipe_block;
	t_list		*pipe_block_list_node;

	pipe_block = malloc(1 * sizeof(t_pipe_blk));
	pipe_block->cmd_one = malloc(1 * sizeof(t_cmd));
	/* TODO protect */
	pipe_block->cmd_one->args = token_array;
	pipe_block->o_fd = STDOUT_FILENO;
	pipe_block->i_fd = STDIN_FILENO;
	/* TODO */
	// pipe_block->cmd_two = ...;
	// pipe_block->pipe[0] = ...;
	// pipe_block->pipe[1] = ...;
	pipe_block_list_node = ft_lstnew((void *)pipe_block);
	/* TODO protect */
	ft_lstadd_back(pipe_block_list, pipe_block_list_node);
	return (0);
}

char	**get_token_array(t_list *tokenlist)
{
	int		token;
	char	**token_array;
	t_token	*current;

	token = 0;
	token_array = malloc((token_chunk_size(tokenlist) + 1) * sizeof(char *));
	if (((t_token *)tokenlist->content)->type == tkn_pipe)
		tokenlist = tokenlist->next;
	while (tokenlist)
	{
		current = ((t_token *)tokenlist->content);
		if (current->type == tkn_pipe)
			break;
		token_array[token] = ft_strdup(current->val);
		token++;
		tokenlist = tokenlist->next;
	}
	token_array[token] = '\0';
	return (token_array);
}

t_list	*make_token_block_list(t_list **tokenlist)
{
	char	**token_array;
	t_list	*token_array_list;
	t_token	*current;

	token_array_list = 0;
	token_array = get_token_array(*tokenlist);
	make_and_add_token_block(&token_array_list, token_array);
	while (*tokenlist)
	{
		current = (*tokenlist)->content;
		if (current->type == tkn_pipe)
		{
			token_array = get_token_array(*tokenlist);
			/* TODO protect */
			make_and_add_token_block(&token_array_list, token_array);
		}
		tokenlist = &(*tokenlist)->next; // let op hier..afwijking
	}
	return (token_array_list);
}
