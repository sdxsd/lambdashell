/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/19 13:22:31 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/04 13:37:08 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_wordcount(const char *s, char c)
{
	int	wc;

	if (!s)
		return (-1);
	wc = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			wc++;
			while (*s != c && *s)
				s++;
		}
	}
	return (wc);
}

static int	ft_gndl(const char *s, char c)
{
	int	iterator;

	iterator = 0;
	while (s[iterator] != c && s[iterator])
		iterator++;
	return (iterator);
}

char	**ft_clean_split(char **s_array)
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

char	**ft_split(char const *s, char c)
{
	char	**s_array;
	size_t	iterator;

	iterator = 0;
	if (!s)
		return (NULL);
	s_array = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!s_array)
		return (NULL);
	while (s_array && iterator < ft_strlen(s))
	{
		while (s[iterator] == c && s[iterator] != '\0')
			iterator++;
		if (s[iterator] != c && s[iterator] != '\0')
		{
			*s_array = ft_strndup(&s[iterator], ft_gndl(&s[iterator], c));
			if (!*s_array)
				return (ft_clean_split(s_array - iterator));
			iterator += ft_gndl(&s[iterator], c);
			s_array += 1;
		}
	}
	*s_array = NULL;
	return (s_array - (ft_wordcount(s, c)));
}

/*
int main()
{
	char	*s = "a//////////";
	char	c = '/';
	char	**s_array = ft_split(s, c);
	
	for (int i = 0; s_array[i] != NULL; i++)
		printf("%s\n", s_array[i]);
}
*/

/*
int main()
{
	char	*s = "MacOS/Windows///GNU_LINUX/FreeBSD/////////OpenBSD/UNIX/";
	char	c = '/';
	char	**s_array = ft_split(s, c);
	
	for (int i = 0; s_array[i] != NULL; i++)
		printf("%s\n", s_array[i]);
}
*/

/*
int main()
{
	char *s = "   split       this for   me  !       ";

	char **s_array = ft_split(s, ' ');
	for (int i = 0; s_array[i] != NULL; i++)
		printf("%s\n", s_array[i]);
}
*/
