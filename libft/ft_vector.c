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

void	*free_vector(t_vector *head, void (*dealloc) (void *))
{
	while (head != NULL)
	{
		if (dealloc != NULL)
			dealloc(head->data);
		free(head);
		head = head->next;
	}
	return (NULL);
}

t_vector	*new_vector_element(t_vector *prev, int idx)
{
	t_vector	*vec;

	vec = malloc(sizeof(t_vector));
	if (!vec)
		return (NULL);
	vec->previous = prev;
	vec->next = NULL;
	vec->data = NULL;
	vec->index = idx;
	return (vec);
}

t_vector	*vec_get_element(t_vector *head, int idx)
{
	if (head->next && head->index != idx)
		return (vec_get_element(head->next, idx));
	else if (head->index == idx)
		return (head);
	else
		return (NULL);
}

int	vec_assign_element(t_vector *head, int idx, void *data)
{
	t_vector	*vec;

	vec = vec_get_element(head, idx);
	if (!vec)
		return (FALSE);
	vec->data = data;
	return (TRUE);
}

t_vector	*alloc_vector(int n_elements)
{
	int			idx;
	t_vector	*vec;
	t_vector	*nxt;
	t_vector	*head;

	idx = 0;
	vec = new_vector_element(NULL, idx);
	if (!vec)
		return (NULL);
	head = vec;
	idx++;
	while (n_elements-- > 0)
	{
		nxt = new_vector_element(vec, idx);
		if (!nxt)
			return (free_vector(head, NULL));
		vec->next = nxt;
		vec = nxt;
		idx++;
	}
	return (head);
}
