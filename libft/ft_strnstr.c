/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:22:23 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/10/20 16:14:44 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *ndl, size_t len)
{
	size_t	c_count;
	size_t	iterator;

	c_count = ft_strlen(ndl);
	iterator = 0;
	if (c_count == 0)
		return ((char *)hs);
	while (hs[iterator] != '\0' && iterator < len)
	{
		if (hs[iterator] == ndl[0])
			if (!ft_strncmp(&hs[iterator], ndl, c_count))
				if (!(c_count + iterator > len))
					return ((char *)&hs[iterator]);
		++iterator;
	}
	return (0);
}

/*
int main()
{
	char *s = "MacOS/Windows/GNU_LINUX/FreeBSD/OpenBSD";
	char *ndl = "Windows";
	char *result = ft_strnstr(s, ndl, ft_strlen(s));
	printf("%s\n", result);
}
*/