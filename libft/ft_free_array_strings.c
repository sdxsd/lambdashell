/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_array_strings.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 19:41:44 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 19:41:50 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array_strings(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free (s[i]);
		s[i] = NULL;
		i++;
	}
	free (s);
	s = NULL;
}
