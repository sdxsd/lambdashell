/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:17:12 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/11 12:56:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_token *token_token;
	t_list *token_list;

	if (!token || (ft_strlen(token) == 0))
		return (1);
	token_token = malloc(sizeof(t_token));
	if (!token_token)
		return (1);
	token_token->val = token;
	token_list = ft_lstnew((void *)token_token);
	if (!token_list)
		return (1);
	ft_lstadd_back(tokens, token_list);
	return (0);
}

/*
tokenizer() ...
*/

// TODO: get len func not good, needs adjusted for considering quotes
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

void	token_add_types(void *token)
{
	((t_token *)token)->type = tkn_str;
	if (((t_token *)token)->val[0] == '<')
		((t_token *)token)->type = tkn_read;
	if (((t_token *)token)->val[0] == '>')
		((t_token *)token)->type = tkn_write;
	if (((t_token *)token)->val[0] == '|')
		((t_token *)token)->type = tkn_pipe;
	if (((t_token *)token)->val[0] == '<' && ((t_token *)token)->val[1] == '<')
		((t_token *)token)->type = tkn_heredoc;
	if (((t_token *)token)->val[0] == '>' && ((t_token *)token)->val[1] == '>')
		((t_token *)token)->type = tkn_append;
}
