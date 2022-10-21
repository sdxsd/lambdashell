/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:24:04 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/10/13 12:44:38 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_c;
	const char	*src_c;

	if (dst == NULL && src == NULL)
		return (dst);
	dst_c = dst;
	src_c = src;
	if (dst > src)
	{
		while (len)
		{
			len--;
			dst_c[len] = src_c[len];
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
