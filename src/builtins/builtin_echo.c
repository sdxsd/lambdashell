/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 12:44:57 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 15:11:07 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

/*
builtin_echo() replicates the real echo command. Similar to the original,
builtin_echo() does not throw an error when parsing multiple "-n" flags
(e.g. echo -n -n -n -n), nor multiple "n" characters following a "-" character
(e.g. -nnnnnnnn).
*/

static int	has_flag_present(char *string)
{
	size_t	i;

	i = 0;
	while (string[i])
	{
		if (string[i] != 'n')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void		builtin_echo(t_cmd *cmd_object, int fd)
{
	size_t	i;
	int		flag_present;

	i = 1;
	flag_present = 0;
	if (cmd_object->args[1])
	{
		while (cmd_object->args[i] && cmd_object->args[i][0] == '-')
		{
			if (has_flag_present(cmd_object->args[i] + 1))
				flag_present = 1;
			else
				break ;
			i++;
		}
		while (cmd_object->args[i])
		{
			ft_putstr_fd(cmd_object->args[i], fd);
			i++;
			if (cmd_object->args[i])
				ft_putstr_fd(" ", fd);
		}
	}
	if (!flag_present)
		ft_putstr_fd("\n", fd);
}
