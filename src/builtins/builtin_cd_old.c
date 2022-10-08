/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd_old.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/07 21:59:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/08 17:17:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_cd(t_cmd *cmd_object, t_list *env)
{
	if (ft_get_n_strings(cmd_object->args) > 2)
	{
		printf("Error. Too many args\n");
		return (1);
	}
	if (ft_strncmp(array[0], "cd", 3) != 0)
		return (1);
	if (array[1] == NULL)
	{
		if (chdir(ev_getenv("HOME", env)))
		{
			perror(array[1]);
			return (1);
		}
		return (0);
	}
	if (chdir(array[1]))
	{
		perror(array[1]);
		return (1);
	}
	return (0);
}