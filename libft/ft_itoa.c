/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/13 10:24:22 by keizerrijk    #+#    #+#                 */
/*   Updated: 2021/11/04 13:36:30 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdlib.h>

static int	ft_isneg(int n)
{
	if (n < 0)
		return (TRUE);
	else
		return (FALSE);
}

static int	ft_numlen(int n)
{
	int	dc;

	if (ft_isneg(n))
		n = -n;
	dc = 2;
	while (n > 10)
	{
		n /= 10;
		dc++;
	}
	return (dc);
}

char	*ft_itoa(int n)
{
	int		iterator;
	int		nstatus;
	char	*str;

	iterator = 0;
	nstatus = ft_isneg(n);
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (nstatus)
		n = -n;
	str = malloc(ft_numlen(n) + ft_isneg(n));
	if (!str)
		return (NULL);
	while (n > 0)
	{
		str[iterator] = (n % 10) + '0';
		n /= 10;
		++iterator;
	}
	if (nstatus)
		str[iterator] = '-';
	str[iterator + nstatus] = '\0';
	return (ft_revstr(str, ft_strlen(str)));
}
