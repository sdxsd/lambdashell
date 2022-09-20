/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug_tokenlist.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 13:30:01 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/20 13:19:52 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
debug_print_tokens_val() is here for debugging purposes. It serves to check what is 
currently stored in the token linked list. It will not be part of the final 
minishell program.
*/

int	debug_print_tokens_val(t_list **tokenlist)
{
	int			i;
	t_list		*list_head;
	t_token		*token_tmp;

	i = 0;
	list_head = (*tokenlist);
	printf("\ndebug_print_tokens_val()\n");
	while (list_head)
	{
		token_tmp = list_head->content;
		printf("[%d]val:%s\n\n", i, token_tmp->val);
		list_head = list_head->next;
		i++;
	}
	return (0);
}

int	debug_print_tokens(t_list **tokenlist)
{
	int			i;
	t_list		*list_head;
	t_token		*token_tmp;

	i = 0;
	list_head = (*tokenlist);
	printf("\ndebug_print_tokens()\n");
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

int	debug_print_token_blks_list(t_list *token_blks_list)
{
	t_list		*current_blk_list;
	t_pipe_blk	*current_pipe_blk;
	size_t		arg_i;
	size_t		blk_i;

	blk_i = 0;
	while(token_blks_list)
	{
		arg_i = 0;
		printf("\nContents of blk [%ld]..\n", blk_i);
		current_blk_list = token_blks_list->content;
		current_pipe_blk = (t_pipe_blk *)current_blk_list;
		while (current_pipe_blk->cmd_one->args[arg_i])
		{
			printf("[%ld]%s\n", arg_i, current_pipe_blk->cmd_one->args[arg_i]);			
			arg_i++;
		}
		blk_i++;
		token_blks_list = token_blks_list->next;
	}
	return (0);
}
