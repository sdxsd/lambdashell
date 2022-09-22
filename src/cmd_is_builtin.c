/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_is_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 21:28:57 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 12:13:44 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

// Rough mockup of function we can use to check if current command is part
// of our builtin function series. Probably needs replacement of "lines".
// General idea remains the same I suppose.

int	cmd_is_builtin(char **lines)
{
	if (ft_strncmp(lines[0], "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(lines[0], "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(lines[0], "env", ft_strlen("env")) == 0)
		return (1);
	if (ft_strncmp(lines[0], "exit", ft_strlen("exit")) == 0)
		return (1);
	if (ft_strncmp(lines[0], "export", ft_strlen("export")) == 0)
		return (1);
	if (ft_strncmp(lines[0], "pwd", ft_strlen("pwd")) == 0)
		return (1);
	if (ft_strncmp(lines[0], "unset", ft_strlen("unset")) == 0)
		return (1);
	return (0);
}
