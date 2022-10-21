/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 16:37:53 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/04 13:48:31 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *s1, size_t len)
{
	char	*dupe_str;

	dupe_str = malloc((sizeof(char) * len) + 1);
	if (!dupe_str)
		return (NULL);
	ft_memcpy(dupe_str, s1, len);
	dupe_str[len] = '\0';
	return (dupe_str);
}
