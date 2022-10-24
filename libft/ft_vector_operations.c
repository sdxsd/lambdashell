/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CODAM C FILE                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire     ########   codam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
THIS FILE IS LICENSED UNDER THE GNU GPLv3
Copyright (C) 2022  Will Maguire

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>

The definition of Free Software is as follows:
				- The freedom to run the program, for any purpose.
				- The freedom to study how the program works, and adapt it to your needs.
				- The freedom to redistribute copies so you can help your neighbor.
				- The freedom to improve the program, and release
				your improvements to the public, so that the whole community benefits.

A program is free software if users have all of these freedoms.
*/

#include "libft.h"
#include <stdlib.h>

static void	update_indices(t_vector *vec, int arg)
{
	if (arg)
		vec->index++;
	else
		vec->index--;
	if (vec->next)
		update_indices(vec->next, arg);
	else
		return ;
}

t_vector	*vector_push_back(t_vector *head, t_vector *new)
{
	head = vector_get_last(head);
	head->next = new;
	new->previous = head;
	new->index = head->index + 1;
	return (new);
}

void	vector_pop_back(t_vector *head, void (*dealloc) (void *))
{
	head = vector_get_last(head);
	head->previous->next = NULL;
	if (dealloc && head->data)
		dealloc(head->data);
	free(head);
}

// NOTE: Requires first element.
t_vector	*vector_push_front(t_vector **head, t_vector *new)
{
	if ((*head)->index != 0)
		return (NULL);
	(*head)->previous = new;
	new->next = *head;
	new->index = 0;
	update_indices(*head, 1);
	*head = new;
	return (new);
}

t_vector	*vector_pop_front(t_vector *head, void (*dealloc) (void *))
{
	t_vector	*new_head;

	head = vector_get_first(head);
	head->next->previous = NULL;
	new_head = head->next;
	if (dealloc && head->data)
		dealloc(head->data);
	update_indices(head, 0);
	free(head);
	return (new_head);
}
