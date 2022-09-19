/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_fd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/19 16:25:08 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/19 16:25:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_fd(void)
{
	if (!isatty(0))
		return(msg_err("init_start()", FAILURE));
	if (!isatty(1))
		return(msg_err("init_start()", FAILURE));
	if (!isatty(2))
		return(msg_err("init_start()", FAILURE));
	return (0);
}
