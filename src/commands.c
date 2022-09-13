/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/05 13:58:26 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/10 18:07:11 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Create function that will check whether the entered command is part of the
builtin commands that we need to manually code. If that's the case, make sure
that the entered command is run with our own implementation, not the official
unix one.
*/

/*
// blabla
int	cmd_is_builtin(t_ms *ms)
{
	if (ft_strncmp(ms->cmd, "pwd", ft_strlen("pwd")))
		return (1);
	return (0);
}
*/
