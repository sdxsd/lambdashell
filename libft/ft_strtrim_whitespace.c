/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim_whitespace.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/16 18:42:57 by sbos          #+#    #+#                 */
/*   Updated: 2022/12/16 18:42:57 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Trims whitespace.
 *
 * @param str
 * @return The trimmed string.
 */
char	*ft_strtrim_whitespace(const char *str)
{
	return (ft_strtrim(str, WHITESPACE_CHARACTERS));
}
