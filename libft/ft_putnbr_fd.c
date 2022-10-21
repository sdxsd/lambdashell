/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:23:21 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/11/04 13:41:35 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= (-1);
	}
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	ft_putnbr_fd(n % 10, fd);
}
