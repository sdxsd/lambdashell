/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean_tokenlist.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 13:24:57 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 13:25:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	clean_tokenlist(t_list **tokenlist)
{
	int			i;
	t_list		*list_head;
	t_token		*token_tmp;
	t_list		*list_tmp;

	i = 0;
	list_head = (*tokenlist);
	while (list_head)
	{
		token_tmp = list_head->content;
		free(token_tmp->val);
		list_tmp = list_head;
		free (list_tmp->content);
		list_head = list_head->next;
		free (list_tmp);
		i++;
	}
	//free (list_tmp->content);
	free (list_head);
	return (0);
}
