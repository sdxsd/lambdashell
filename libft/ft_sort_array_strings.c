/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_array_strings.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 18:39:22 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 18:42:56 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_array_strings(char **lines)
{
	int		i;
	int		j;
	int		n_lines;
	char	*tmp;

	i = 0;
	n_lines = ft_get_n_strings(lines);
	while ((i <= n_lines) && (lines[i]))
	{
		j = i;
		j++;
		while ((j <= n_lines) && lines[j])
		{
			if (ft_memcmp(lines[i], lines[j], ft_strlen(lines[j])) > 0)
			{
				tmp = lines[i];
				lines[i] = lines[j];
				lines[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
