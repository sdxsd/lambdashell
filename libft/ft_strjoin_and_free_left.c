/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_and_free_left.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 16:02:04 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/29 16:02:04 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_and_free_left(char *left, char *right)
{
	char	*result;

	result = ft_strjoin(left, right);
	ft_free(&left);
	return (result);
}
