/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 18:24:05 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/18 11:53:41 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	msg_err(char *s, int ret)
{
	perror(s);
	return (ret);
}

void	*null_msg_err(char *s)
{
	msg_err(s, 0);
	return (NULL);
}
