/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:22:58 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/11/04 13:37:47 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*dupe_str;

	dupe_str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dupe_str)
		return (NULL);
	else
	{
		ft_memcpy(dupe_str, s1, ft_strlen((s1)));
		dupe_str[ft_strlen((char *)s1)] = '\0';
		return (dupe_str);
	}
}
