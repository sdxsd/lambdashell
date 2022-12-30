/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_and_free_left_right.c                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 16:02:04 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/29 16:02:04 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_and_free_left_right(char *left, char **right_ptr)
{
	char	*joined;

	joined = ft_strjoin_and_free_left(left, *right_ptr);
	ft_free(right_ptr);
	return (joined);
}
