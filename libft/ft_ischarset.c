/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ischarset.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 21:14:48 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/09 21:17:57 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ischarset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}
