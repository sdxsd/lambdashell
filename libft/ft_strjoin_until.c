/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_until.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 13:54:42 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/12 13:57:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_until(char const *s1, char const *s2, size_t until)
{
	char	*s_join;

	if (!(s1) || !(s2) || until <= 0)
		return (NULL);
	s_join = ft_calloc((ft_strlen(s1) + until + 1), sizeof(char));
	if (!(s_join))
		return (NULL);
	ft_memcpy(s_join, s1, ft_strlen(s1));
	ft_memcpy(s_join + ft_strlen(s1), s2, until);
	return (s_join);
}
