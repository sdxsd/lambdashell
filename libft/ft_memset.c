/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:24:00 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/10/20 16:43:14 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*ptr;

	ptr = b;
	while (len != 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		--len;
	}
	return (b);
}
