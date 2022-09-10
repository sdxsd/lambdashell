/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:38:27 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/10 18:42:58 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dbg_print_env(t_ms *ms)
{
	t_env *cur;
	cur = *ms->env;
	while (cur->next)
	{
		printf("%s=%s\n", cur->key, cur->val);
		cur = cur->next;
	}
	printf("%s=%s\n", cur->key, cur->val);
	return (1);
}

int	dbg_print_env_keys(t_ms *ms)
{
	t_env *cur;
	cur = *ms->env;
	while (cur->next)
	{
		printf("%s\n", cur->key);
		cur = cur->next;
	}
	printf("%s\n", cur->key);
	return (1);
}

int	dbg_print_env_idx(t_ms *ms)
{
	t_env *cur;
	cur = *ms->env;
	while (cur->next)
	{
		printf("[%d] %s=%s\n", cur->idx, cur->key, cur->val);
		cur = cur->next;
	}
	printf("[%d] %s=%s\n", cur->idx, cur->key, cur->val);
	return (1);
}

/*
dbg_print_tokens_txt() is here for debugging purposes. It serves to check what is 
currently stored in the token linked list. It will not be part of the final 
minishell program.
*/

int	dbg_print_tokens_txt(t_list **tokenlist)
{
	int			i;
	t_list		*list_head;
	t_token		*token_tmp;

	i = 0;
	list_head = (*tokenlist);
	printf("\ndbg_print_tokens_txt()\n");
	while (list_head)
	{
		token_tmp = list_head->content;
		printf("[%d]txt:%s\n\n", i, token_tmp->txt);
		list_head = list_head->next;
		i++;
	}
	return (0);
}

int	dbg_print_tokens(t_list **tokenlist)
{
	int			i;
	t_list		*list_head;
	t_token		*token_tmp;

	i = 0;
	list_head = (*tokenlist);
	printf("\ndbg_print_tokens()\n");
	while (list_head)
	{
		token_tmp = list_head->content;
		printf("[%d]txt:%s\n", i, token_tmp->txt);
		printf("[%d]tag:%d\n\n", i, token_tmp->tag);
		list_head = list_head->next;
		i++;
	}
	return (0);
}
