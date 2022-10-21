/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmaguire <wmaguire@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:24:18 by keizerrijk        #+#    #+#             */
/*   Updated: 2021/10/20 21:56:06 by wmaguire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			iterator;
	const char		*str_ptr;

	iterator = 0;
	str_ptr = s;
	while (iterator < n)
	{
		if ((unsigned char)str_ptr[iterator] == (unsigned char)c)
			return ((void *)&str_ptr[iterator]);
		++iterator;
	}
	return (NULL);
}
