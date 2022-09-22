/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_until_char.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 19:29:13 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 19:29:23 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_print_until_char(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}
