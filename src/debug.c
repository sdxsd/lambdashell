/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/25 14:38:27 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/14 20:55:20 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
dbg_print_tokens_val() is here for debugging purposes. It serves to check what is 
currently stored in the token linked list. It will not be part of the final 
minishell program.
*/

int	dbg_print_tokens_val(t_list **tokenlist)
{
	int			i;
	t_list		*list_head;
	t_token		*token_tmp;

	i = 0;
	list_head = (*tokenlist);
	printf("\ndbg_print_tokens_val()\n");
	while (list_head)
	{
		token_tmp = list_head->content;
		printf("[%d]val:%s\n\n", i, token_tmp->val);
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
		printf("[%d]val:%s\n", i, token_tmp->val);
		printf("[%d]type:%d\n\n", i, token_tmp->type);
		list_head = list_head->next;
		i++;
	}
	return (0);
}

int	dbg_print_token_block_list(t_list *token_block_list)
{
	t_list		*current_block_list;
	t_pipe_blk	*current_pipe_block;
	size_t		arg_i;
	size_t		block_i;

	block_i = 0;
	while(token_block_list)
	{
		arg_i = 0;
		printf("\nContents of block [%ld]..\n", block_i);
		current_block_list = token_block_list->content;
		current_pipe_block = (t_pipe_blk *)current_block_list;
		while (current_pipe_block->cmd_one->args[arg_i])
		{
			printf("[%ld]%s\n", arg_i, current_pipe_block->cmd_one->args[arg_i]);			
			arg_i++;
		}
		block_i++;
		token_block_list = token_block_list->next;
	}
	return (0);
}
