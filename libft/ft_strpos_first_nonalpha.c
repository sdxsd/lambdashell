/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strpos_first_nonalpha                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 15:45:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/09 15:46:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strpos_first_nonalpha(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalpha(s[i]))
			break;
		i++;
	}
	return (i);
}
