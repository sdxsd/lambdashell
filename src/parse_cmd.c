/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 12:59:42 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/22 15:43:41 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
/*
int	parse_cmd(char **full_cmd)
{
	struct stat	statbuf;
	int	status;
	
	status = lstat(full_cmd[0], &statbuf);
	if (status == 0)
	{
		if (S_IFDIR(statbuf.st_mode))
		{
			
		}
	}
}
*/