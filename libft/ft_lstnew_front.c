/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 19:23:39 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/10/14 19:40:28 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew_front(t_list **lst_ptr, void *content)
{
	t_list	*new_lst;

	new_lst = ft_lstnew(content);
	if (new_lst == NULL)
		return (NULL);
	ft_lstadd_front(lst_ptr, new_lst);
	return (new_lst);
}
