/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 13:27:37 by sbos          #+#    #+#                 */
/*   Updated: 2021/11/03 16:42:02 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Frees a variable pointing to something allocated,
 * and sets the variable to NULL so double free crashes can't occur on it.
 * Example: char *str = malloc(42); ft_free(&str); ft_free(&str);
 * This function is written so that it even handles when a struct member
 * is freed that points to its parent struct.
 *
 * @param ptrptr This should be the address of a variable pointing to
 * something that has been allocated, like a string.
 */
void	ft_free(void *ptrptr)
{
	void		**_ptrptr;
	void		*ptr;

	_ptrptr = ptrptr;
	ptr = *_ptrptr;
	*_ptrptr = NULL;
	free(ptr);
}
