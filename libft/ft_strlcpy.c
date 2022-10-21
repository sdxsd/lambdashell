/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 17:15:24 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/10/26 15:35:53 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	iterator;

	if (dstsize <= 0)
		return (ft_strlen(src));
	iterator = 0;
	while (src[iterator] != '\0' && iterator < (dstsize - 1))
	{
		dst[iterator] = src[iterator];
		iterator++;
	}
	if (dstsize > 0)
		dst[iterator] = '\0';
	return (ft_strlen(src));
}
