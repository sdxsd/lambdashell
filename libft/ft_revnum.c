/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_revnum.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/16 17:23:04 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/16 17:34:25 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_revnum(size_t nb)
{
	size_t	rem;
	size_t	reversed;

	reversed = 0;
	while (nb != 0)
	{
		rem = nb % 10;
		reversed = reversed * 10 + rem;
		nb /= 10;
	}
	return (reversed);
}
