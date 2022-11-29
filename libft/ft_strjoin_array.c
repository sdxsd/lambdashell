/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_array.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/29 16:02:04 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/29 16:02:04 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_array(char *array[])
{
	char	*result;

	if (!array[0])
		return (NULL);
	if (!array[1])
		return (ft_strdup(array[0]));
	result = ft_strjoin(array[0], array[1]);
	if (!result)
		return (NULL);
	array += 2;
	while (*array != NULL)
	{
		result = ft_strjoin_and_free_left(result, *array);
		if (!result)
			return (NULL);
		array++;
	}
	return (result);
}
