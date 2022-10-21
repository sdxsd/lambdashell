/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 15:55:44 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/04 11:54:32 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// Returns true if parameter x is within the set of chars
// to be trimmed. 
static int	ft_setcmp(char x, const char *set)
{
	int	iter;

	iter = 0;
	while (set[iter] != '\0')
	{
		if (x == set[iter])
			return (TRUE);
		else
			iter++;
	}
	return (FALSE);
}

static unsigned int	ft_deter_strlen(const char *s1, const char *set)
{
	unsigned int	iter;
	unsigned int	strlen;
	unsigned int	n_strlen;

	iter = 0;
	strlen = ft_strlen(s1);
	if (!strlen)
		return (0);
	n_strlen = strlen;
	while (iter < strlen && ft_setcmp(s1[iter], set))
	{
		iter++;
		n_strlen--;
	}
	iter = strlen - 1;
	while (iter > 0 && ft_setcmp(s1[iter], set))
	{
		iter--;
		n_strlen--;
	}
	if (n_strlen > strlen)
		return (0);
	return (n_strlen);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		iter;
	int		n_strlen;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	iter = 0;
	n_strlen = ft_deter_strlen(s1, set);
	while (ft_setcmp(s1[iter], set))
		iter++;
	str = ft_strndup(&s1[iter], n_strlen);
	if (!str)
		return (NULL);
	return (str);
}

/*
int main()
{
	char *s = "  \t \t \n   \n\n\n\t";
	char *set = " \n\t";
	printf("%s", ft_strtrim(s, set));
}
*/
