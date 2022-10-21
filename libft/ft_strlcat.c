/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/25 20:12:08 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/10/27 13:31:23 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	iterator;
	size_t	offset;

	offset = ft_strlen(dst);
	iterator = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (offset == dstsize)
		return (offset + ft_strlen(src));
	if (offset > dstsize)
		return (ft_strlen(src) + dstsize);
	while (iterator < (dstsize - offset - 1) && src[iterator] != '\0')
	{
		dst[iterator + offset] = src[iterator];
		iterator++;
	}
	dst[iterator + offset] = '\0';
	return (offset + ft_strlen(src));
}

/*
int main()
{
	char str[20] = "";
	char *str2 = "LINUX";
	size_t max = (ft_strlen(str) + ft_strlen(str2) + 1);

	ft_strlcat(&str[0], str2, max);
	max++;
	printf("%s", &str[0]);
}
*/
