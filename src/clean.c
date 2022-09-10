/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:07:36 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/11 01:41:36 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_tokens(t_list **tokenlist)
{
	int			i;
	t_list		*list_head;
	t_token		*token_tmp;
	t_list		*tmp;

	i = 0;
	list_head = (*tokenlist);
	while (list_head)
	{
		token_tmp = list_head->content;
		free(token_tmp->txt);
		tmp = list_head;
		list_head = list_head->next;
		free (tmp);
		i++;
	}
	free (list_head);
	return (0);
}

int	clean_env(t_env **env)
{
	t_env *tmp1;
	t_env *tmp2;

	tmp1 = (*env);
	while (tmp1)
	{
		free (tmp1->key);
		free (tmp1->val);
		tmp2 = tmp1->next;
		free (tmp1);
		tmp1 = tmp2;
	}
	free (tmp1);
	free (env);
	return (0);
}
