/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strpos_charset.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 20:11:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/06 20:11:52 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strpos_charset(char *s, char *charset)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(charset, s[i]))
			break;
		i++;
	}
	return (i);
}
