/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 15:45:14 by wmaguire      #+#    #+#                 */
/*   Updated: 2021/11/15 18:03:10 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr(char *str)
{
	int	iterator;

	if (!str)
	{
		ft_putstr("(null)");
		return ;
	}
	iterator = 0;
	while (str[iterator] != '\0')
	{
		write(1, &str[iterator], 1);
		++iterator;
	}
}
