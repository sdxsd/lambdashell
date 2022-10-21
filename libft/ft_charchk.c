/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_charchk.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 10:24:22 by keizerrijk    #+#    #+#                 */
/*   Updated: 2022/02/01 13:36:30 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charchk(int tc, char *dict)
{
	int	iterator;

	iterator = 0;
	while (dict[iterator] != '\0')
	{
		if (tc == dict[iterator])
			return (1);
		iterator++;
	}
	return (0);
}
