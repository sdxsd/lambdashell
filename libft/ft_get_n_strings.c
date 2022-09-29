/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_n_strings.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 18:41:31 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 18:42:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_n_strings(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}
