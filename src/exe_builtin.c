/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 12:17:54 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 15:05:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

// Note: for env, we currently hard-code that it uses ft_putrstr_fd() fd = 1.

int	exe_builtin(t_cmd *cmd_object, t_ms *ms)
{
	if (ft_strcmp(cmd_object->args[0], "env") == 0)
		builtin_env(ms, 1); // fd = 1
	if (ft_strcmp(cmd_object->args[0], "pwd") == 0)
		builtin_pwd();
	if (ft_strcmp(cmd_object->args[0], "unset") == 0)
		builtin_unset(cmd_object->args, ms);
	if (ft_strcmp(cmd_object->args[0], "echo") == 0)
		builtin_echo(cmd_object->args, ms);
	// to add: exit, export, cd. Each of white still needs to be made.
	return (0);
}
