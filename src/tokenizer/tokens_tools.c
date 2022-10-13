#include "../includes/minishell.h"

/* void	tokens_add_types(t_exec_element *tokenlist) */
/* { */
/* 	t_exec_element	*curr; */

/* 	if (!(tokenlist)) */
/* 		return ; */
/* 	while (tokenlist) */
/* 	{ */
/* 		curr = tokenlist->line; */
/* 		curr->type = tkn_str; */
/* 		if (curr->val[0] == '<') */
/* 			curr->type = tkn_read; */
/* 		if (curr->val[0] == '>') */
/* 			curr->type = tkn_write; */
/* 		if (curr->val[0] == '|') */
/* 			curr->type = tkn_pipe; */
/* 		if (curr->val[0] == '<' && curr->val[1] == '<') */
/* 			curr->type = tkn_heredoc; */
/* 		if (curr->val[0] == '>' && curr->val[1] == '>') */
/* 			curr->type = tkn_append;	 */
/* 		tokenlist = tokenlist->next; */
/* 	} */
/* } */

/* int	tokens_check_syntax(t_exec_element *tokenlist) */
/* { */
/* 	t_exec_element	*current; */
/* 	t_exec_element	*next; */

/* 	if ((((t_exec_element *)tokenlist->line)->type == tkn_pipe) || \ */
/* 	(((t_token *)ft_lstlast(tokenlist)->content)->type != tkn_str)) */
/* 		return (1); */
/* 	if ((t_token *)tokenlist->next == NULL) */
/* 		return (0); */
/* 	while (tokenlist && tokenlist->next) */
/* 	{ */
/* 		current = (t_token *)tokenlist->content; */
/* 		next = (t_token *)tokenlist->next->content; */
/* 		if (current->type == tkn_read && next->type != tkn_str) */
/* 				return(msg_err("< was not followed by string\n", 1)); */
/* 		if (current->type == tkn_write && next->type != tkn_str) */
/* 				return(msg_err("> was not followed by string\n", 1)); */
/* 		if (current->type == tkn_pipe && next->type == tkn_pipe) */
/* 				return(msg_err("| was followed by |\n", 1)); */
/* 		if (current->type == tkn_heredoc && next->type != tkn_str) */
/* 				return(msg_err("<< was not followed by string\n", 1)); */
/* 		if (current->type == tkn_append && next->type != tkn_str) */
/* 				return(msg_err(">> was not followed by string\n", 1)); */
/* 		tokenlist = tokenlist->next; */
/* 	} */
/* 	return (0); */
/* } */
