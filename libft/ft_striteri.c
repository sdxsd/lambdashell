/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/04 12:04:59 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/04 12:30:55 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	iterator;

	if (!s || !f)
		return ;
	iterator = 0;
	while (s[iterator] != '\0')
	{
		(*f)(iterator, s + iterator);
		iterator++;
	}
}
