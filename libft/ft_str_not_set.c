/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_not_set.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 12:52:46 by sbos          #+#    #+#                 */
/*   Updated: 2022/07/14 14:47:42 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Returns a pointer to the first character which isn't part
 * of the @p set characters.
 *
 * @param haystack
 * @param set
 * @return A pointer to the first spot where one of the non-set characters
   is found;\nNULL if no spot is found or @p set is an empty string.
 */
char	*ft_str_not_set(char *haystack, char *set)
{
	while (*haystack)
	{
		if (!ft_strchr(set, *haystack))
			return (haystack);
		haystack++;
	}
	return (NULL);
}
