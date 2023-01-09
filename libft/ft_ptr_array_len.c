/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ptr_array_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/30 19:34:17 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/30 19:34:17 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ptr_array_len(void **ptr_array)
{
	size_t	size;

	size = 0;
	while (ptr_array[size] != NULL)
		++size;
	return (size);
}
