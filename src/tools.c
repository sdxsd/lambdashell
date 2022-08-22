/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 15:13:49 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/22 17:04:43 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	substring_start(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && (i != ft_strlen(s2)))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
