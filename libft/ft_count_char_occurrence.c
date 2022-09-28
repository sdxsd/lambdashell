/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count_char_occurrence.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/28 15:41:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/28 15:41:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_char_occurrence(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
		}
		i++;
	}
	return (count);
}
