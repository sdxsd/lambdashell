/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 18:00:42 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/04 13:37:58 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*b_str;
	int		s1_l;
	int		s2_l;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	str = malloc((s1_l + s2_l) + 1);
	if (!str)
		return (NULL);
	b_str = str;
	ft_strncpy(str, (char *)s1, s1_l);
	str += s1_l;
	ft_strncpy(str, (char *)s2, s2_l);
	str += s2_l;
	*str = '\0';
	return (b_str);
}

/*
int	main(void)
{
	char	*s1 = "GNU/";
	char	*s2 = "LINUX";
	ft_putstr(ft_strjoin(s1, s2));
}
*/
