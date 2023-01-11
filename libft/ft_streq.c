/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_streq.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sbos <sbos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/14 14:27:49 by sbos          #+#    #+#                 */
/*   Updated: 2022/11/14 14:27:49 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_streq(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (false);
	return (ft_strcmp(s1, s2) == 0);
}
