/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 15:29:03 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/18 15:48:48 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

int	ft_putchar_len(char c)
{
	return (write(1, &c, 1));
}

static int	edgelord_hex(unsigned int nb, unsigned int mode)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		return (ft_puthex(nb, mode));
}

int	handle_variable(const char spec, va_list arglist)
{
	if (spec == 'c')
		return (ft_putchar_len(va_arg(arglist, int)));
	else if (spec == '%')
		return (ft_putchar_len('%'));
	else if (spec == 's')
		return (ft_putstr_len(va_arg(arglist, char *)));
	else if (spec == 'd' || spec == 'i')
		return (ft_putnbr_len(va_arg(arglist, int)));
	else if (spec == 'p')
		return (ft_putvoid(va_arg(arglist, size_t)));
	else if (spec == 'x')
		return (edgelord_hex(va_arg(arglist, unsigned int), 0));
	else if (spec == 'X')
		return (edgelord_hex(va_arg(arglist, size_t), 1));
	else if (spec == 'u')
		return (ft_unsigned_putnbr(va_arg(arglist, unsigned int)));
	else if (spec != '\0')
		return (ft_putchar_len(spec));
	else
		return (0);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	arglist;
	int		iterator;
	int		x;

	iterator = 0;
	x = 0;
	va_start(arglist, fmt);
	while (fmt[iterator] != '\0')
	{
		if (fmt[iterator] == '%')
		{
			x += handle_variable(fmt[iterator + 1], arglist);
			if (fmt[iterator + 1] != '\0')
				iterator++;
		}
		else
			x += ft_putchar_len(fmt[iterator]);
		iterator++;
	}
	va_end(arglist);
	return (x);
}
