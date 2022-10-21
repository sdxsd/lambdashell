/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:22:28 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/10/20 16:18:32 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	iterator;

	iterator = 0;
	while (iterator < n && src[iterator] != '\0')
	{
		dest[iterator] = src[iterator];
		++iterator;
	}
	while (iterator < n)
	{
		dest[iterator] = '\0';
		iterator++;
	}
	return (dest);
}
