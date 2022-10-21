/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/09 11:30:45 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/07/09 11:30:50 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putchar(char c);

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
