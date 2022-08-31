/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 18:24:05 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/29 18:24:16 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msg_err(char *s, int ret)
{
	printf("Error: ");
	printf("%s\n", s);
	return (ret);
}
