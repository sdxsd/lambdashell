/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:23:03 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/11/04 16:49:29 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		iterator;

	iterator = 0;
	while (s[iterator] != (unsigned char)c && s[iterator] != '\0')
		++iterator;
	if (s[iterator] == (unsigned char)c)
		return ((char *)s + iterator);
	else
		return (NULL);
}
