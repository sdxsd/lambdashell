/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:24:35 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 11:58:37 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// TODO!
int	init_env(t_ms *ms, char **envp)
{
	(void)ms;
	(void)envp;
	return (0);
}

int	init_ms(void)
{
	if (!isatty(0))
		return(msg_err("Standard input fd does not refer to terminal.", 1));
	if (!isatty(1))
		return(msg_err("Standard output fd does not refer to terminal.", 1));
	if (!isatty(2))
		return(msg_err("Standard error fd does not refer to terminal.", 1));	
	return (0);
}
