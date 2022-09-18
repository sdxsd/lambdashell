/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:17:12 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 13:36:56 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
The tokenizer is also known as the "lexer". 
This section contains files for the tokenization chapter. It cuts the expanded
input string into words and chains these words together in a linked list.
*/

/*
token_make_and_add() ...
*/

int	token_make_and_add(char *token, t_list **tokens)
{
	t_token	*token_token;
	t_list	*token_list;

	if (!token || (ft_strlen(token) == 0))
		return (1);
	token_token = malloc(sizeof(t_token));
	if (!token_token)
		return (1);
	token_token->val = token;
	token_list = ft_lstnew(token_token);
	if (!token_list)
		return (1);
	ft_lstadd_back(tokens, token_list);
	return (0);
}

void	token_add_types(t_list *tokenlist)
{
	t_token	*curr;

	if (!(tokenlist))
		return ;
	while (tokenlist)
	{
		curr = tokenlist->content;
		curr->type = tkn_str;
		if (curr->val[0] == '<')
			curr->type = tkn_read;
		if (curr->val[0] == '>')
			curr->type = tkn_write;
		if (curr->val[0] == '|')
			curr->type = tkn_pipe;
		if (curr->val[0] == '<' && curr->val[1] == '<')
			curr->type = tkn_heredoc;
		if (curr->val[0] == '>' && curr->val[1] == '>')
			curr->type = tkn_append;	
		tokenlist = tokenlist->next;
	}
}

int	token_checker(t_list *tokenlist)
{
	t_token	*current;
	t_token	*next;

	if ((((t_token *)tokenlist->content)->type == tkn_pipe) || \
	(((t_token *)ft_lstlast(tokenlist)->content)->type != tkn_str))
		return (1);
	if ((t_token *)tokenlist->next == NULL)
		return (0);
	while (tokenlist && tokenlist->next)
	{
		current = (t_token *)tokenlist->content;
		next = (t_token *)tokenlist->next->content;
		if (current->type == tkn_read && next->type != tkn_str)
				return(msg_err("< was not followed by string\n", 1));
		if (current->type == tkn_write && next->type != tkn_str)
				return(msg_err("> was not followed by string\n", 1));
		if (current->type == tkn_pipe && next->type == tkn_pipe)
				return(msg_err("| was followed by |\n", 1));
		if (current->type == tkn_heredoc && next->type != tkn_str)
				return(msg_err("<< was not followed by string\n", 1));
		if (current->type == tkn_append && next->type != tkn_str)
				return(msg_err(">> was not followed by string\n", 1));
		tokenlist = tokenlist->next;
	}
	return (0);
}
