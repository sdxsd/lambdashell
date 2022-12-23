/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 12:52:46 by sbos          #+#    #+#                 */
/*   Updated: 2022/07/14 14:47:42 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns a pointer to the first spot where one of the @p set characters
 * is found.
 *
 * @param haystack
 * @param set
 * @return A pointer to the first spot where one of the @p set characters
   is found;\nNULL if no spot is found or @p set is an empty string.
 */
char	*ft_strset(char *haystack, char *set)
{
	char	*x;

	x = NULL;
	while (*set)
	{
		x = ft_strchr(haystack, *set);
		if (x)
			return (x);
		set++;
	}
	return (x);
}
