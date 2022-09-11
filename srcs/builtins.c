/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/26 16:25:57 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/10 18:06:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ms_pwd() imitates pwd().
*/

int	ms_pwd(void)
{
	char	pwd[4096];

	if (getcwd(pwd, 4096) == NULL)
		return (1);
	printf("%s\n", pwd);
	return (0);
}
