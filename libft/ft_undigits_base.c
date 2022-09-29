/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_undigits_base.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 16:49:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 16:36:32 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_undigits_base(unsigned long long n, int base)
{
	int	ndigits;

	if (n == 0)
		return (1);
	ndigits = 0;
	while (n > 0)
	{
		n = n / base;
		ndigits++;
	}
	return (ndigits);
}
