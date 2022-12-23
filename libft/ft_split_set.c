/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_set.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 13:22:31 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/04 13:37:08 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_wordcount(const char *s, char *set)
{
	int	wc;

	if (!s)
		return (-1);
	wc = 0;
	while (*s)
	{
		if (ft_strchr(set, *s))
			s++;
		if (!ft_strchr(set, *s) && *s != '\0')
		{
			wc++;
			while (!ft_strchr(set, *s) && *s)
				s++;
		}
	}
	return (wc);
}

static int	ft_gndl(const char *s, char *set)
{
	int	iterator;

	iterator = 0;
	while (!ft_strchr(set, s[iterator]) && s[iterator])
		iterator++;
	return (iterator);
}

static char	**ft_clean_split(char **s_array)
{
	while (s_array)
	{
		if (*s_array)
			free(*s_array);
		s_array += 1;
	}
	free(s_array);
	return ((char **)0x0);
}

char	**ft_split_set(char const *s, char *set)
{
	char	**s_array;
	size_t	iterator;

	iterator = 0;
	if (!s)
		return (NULL);
	s_array = malloc(sizeof(char *) * (ft_wordcount(s, set) + 1));
	if (!s_array)
		return (NULL);
	while (s_array && iterator < ft_strlen(s))
	{
		while (ft_strchr(set, s[iterator]) && s[iterator] != '\0')
			iterator++;
		if (!ft_strchr(set, s[iterator]) && s[iterator] != '\0')
		{
			*s_array = ft_strndup(&s[iterator], ft_gndl(&s[iterator], set));
			if (!*s_array)
				return (ft_clean_split(s_array - iterator));
			iterator += ft_gndl(&s[iterator], set);
			s_array += 1;
		}
	}
	*s_array = NULL;
	return (s_array - (ft_wordcount(s, set)));
}
