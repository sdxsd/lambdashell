/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 11:30:14 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/12 11:30:14 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	size_t			i;
	size_t			len;
	unsigned char	*b_uc;
	unsigned char	c;

	ptr = malloc(count * size);
	if (!(ptr))
		return (NULL);
	i = 0;
	len = count * size;
	b_uc = (unsigned char *)ptr;
	c = 0;
	while (i < len)
	{
		b_uc[i] = c;
		i++;
	}
	return (ptr);
}
