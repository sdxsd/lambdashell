/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:23:51 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/10/20 16:36:58 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
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
	ft_putchar_fd('\n', fd);
}
