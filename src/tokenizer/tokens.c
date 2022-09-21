/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 13:32:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/20 22:00:21 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
tokens_populate_tokenlist() scans the input line and isolates every word and turns it into a
"token", which will be chained together in a linked list. Here, each node
contains a "value" variable (i.e. the char array for the isolated word), and a
"type" variable, describing the category to which the token belongs (e.g. 
string, write operator, read operator, etc.)

IMPORTANT: The function below is not finished. Text between single quotes
should not be divided into separate tokens. 
*/

/*
char	*tokens_get_array(char *line)
{
	char	*token_array;
	size_t	token_end;
	size_t	token_start;

	token_start = 0;
	while (ft_ischarset(line[token_start], " $\t\v\r\n\f"))
		token_start++;
	token_end = ft_strpos_charset(&line[token_start], " $\t\v\r\n\f");
	token_array = ft_substr(&line[token_start], 0, token_end);
	if (ft_strlen(token_array) == 0)
		return (NULL);
	return (token_array);
}
*/

/*
int	tokens_populate_tokenlist(char *line, t_list **tokens)
{
	size_t	token_start;
	char	*token_array;
	int		token_end;

	token_start = 0;
	token_end = 0;
	while (token_start < ft_strlen(line))
	{
		token_array = tokens_get_array(&line[token_start]);
		if (!token_array)
			return (1);
		token_end = ft_strlen(token_array);
		tokens_make_and_add(token_array, tokens);
		token_start = token_start + token_end + 1;
	}
	return (0);
}
*/


// TODO HERE..NOT WORKING!

int	tokens_populate_tokenlist(char **lines, t_list **tokens)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		tokens_make_and_add(lines[i], tokens);
		i++;
	}
	return (0);
}



int	tokens_make_and_add(char *token_array, t_list **tokens)
{
	t_token	*token_obj;
	t_list	*token_list_elem;

	if (!token_array || (ft_strlen(token_array) == 0))
		return (1);
	token_obj = malloc(sizeof(t_token));
	if (!token_obj)
		return (1);
	token_obj->val = ft_strdup(token_array);
	if (!token_obj->val)
		return (1);
	free (token_array);
	token_list_elem = ft_lstnew(token_obj);
	if (!token_list_elem)
		return (1);
	ft_lstadd_back(tokens, token_list_elem);
	return (0);
}

int	tokens_get_pipe_blk_len(t_list *tokenlist)
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

int	tokens_make_and_add_token_blk(t_list **pipe_blk_list, char **token_array)
{
	t_pipe_blk	*pipe_blk;
	t_list		*pipe_blk_list_node;

	pipe_blk = malloc(1 * sizeof(t_pipe_blk));
	pipe_blk->cmd_one = malloc(1 * sizeof(t_cmd));
	/* TODO protect */
	pipe_blk->cmd_one->args = token_array;
	pipe_blk->o_fd = STDOUT_FILENO;
	pipe_blk->i_fd = STDIN_FILENO;
	/* TODO */
	// pipe_blk->cmd_two = ...;
	// pipe_blk->pipe[0] = ...;
	// pipe_blk->pipe[1] = ...;
	pipe_blk_list_node = ft_lstnew((void *)pipe_blk);
	/* TODO protect */
	ft_lstadd_back(pipe_blk_list, pipe_blk_list_node);
	return (0);
}

char	**get_tokens_array(t_list *tokenlist)
{
	int		token;
	char	**token_array;
	t_token	*current;

	token = 0;
	token_array = malloc((tokens_get_pipe_blk_len(tokenlist) + 1) * sizeof(char *));
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

t_list	*make_token_blks_list(t_list **tokenlist)
{
	char	**token_array;
	t_list	*token_array_list;
	t_token	*current;

	token_array_list = 0;
	token_array = get_tokens_array(*tokenlist);
	tokens_make_and_add_token_blk(&token_array_list, token_array);
	while (*tokenlist)
	{
		current = (*tokenlist)->content;
		if (current->type == tkn_pipe)
		{
			token_array = get_tokens_array(*tokenlist);
			/* TODO protect */
			tokens_make_and_add_token_blk(&token_array_list, token_array);
		}
		tokenlist = &(*tokenlist)->next; // let op hier..afwijking
	}
	return (token_array_list);
}
