/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlen_t.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/16 17:48:48 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/16 17:52:17 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen_t(size_t n)
{
	size_t	dc;

	dc = 2;
	while (n > 10)
	{
		n /= 10;
		dc++;
	}
	return (dc);
}
