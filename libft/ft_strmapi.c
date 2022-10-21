/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 11:37:18 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/10/13 12:31:11 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	int		len;
	int		iterator;
	char	*n_str;

	if (s == NULL || f == NULL)
		return (NULL);
	iterator = 0;
	len = ft_strlen(s);
	n_str = ft_strdup(s);
	if (n_str == NULL)
		return (NULL);
	while (iterator < len)
	{
		n_str[iterator] = (*f)(iterator, s[iterator]);
		++iterator;
	}
	return (n_str);
}
