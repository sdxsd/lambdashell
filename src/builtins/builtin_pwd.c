/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/17 20:59:54 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 15:07:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>

/*
NOTE:
_POSIX_PATH_MAX is used to maintain compatibility on
POSIX compatible systems. This ensures that the buffer size of pwd
is always large enough to hold the path.
*/

int	builtin_pwd(int fd)
{
	char	pwd[_POSIX_PATH_MAX];

	if (getcwd(pwd, _POSIX_PATH_MAX) == NULL)
		return (1);
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	return (0);
}
