/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:23:16 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/10/13 12:35:09 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	iterator;

	if (s == NULL)
		return ;
	iterator = 0;
	while (s[iterator] != 0)
	{
		ft_putchar_fd(s[iterator], fd);
		++iterator;
	}
}
