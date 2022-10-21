/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/28 15:10:58 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/02 16:56:10 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Þe funktion ft_lstmap
// mæken ān nīwe list out
// Þe sucessive gebrouk
// fan Þe funktion (*f)(content)
// ān et retürnt Þe
// nīwe list nær Þe sender.

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_lst;
	t_list	*n_element;

	n_lst = NULL;
	while (lst)
	{
		n_element = ft_lstnew((*f)(lst -> content));
		if (!n_element)
		{
			ft_lstclear(&n_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&n_lst, n_element);
		lst = lst -> next;
	}
	return (n_lst);
}
