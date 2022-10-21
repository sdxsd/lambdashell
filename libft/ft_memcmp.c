/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmaguire <wmaguire@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:24:14 by keizerrijk        #+#    #+#             */
/*   Updated: 2021/10/13 11:27:19 by wmaguire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*str_1;
	const unsigned char		*str_2;
	size_t					iterator;

	str_1 = s1;
	str_2 = s2;
	iterator = 0;
	while (iterator < n)
	{
		if (str_1[iterator] != str_2[iterator])
			return ((str_1[iterator] - str_2[iterator]));
		++iterator;
	}
	return (FALSE);
}
