/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_builtin.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 12:17:54 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 15:34:41 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

// Note: for env and pwd, we currently hard-code that it uses ft_putrstr_fd() fd = 1.


/*
Your shell must implement the following builtins:
- echo with option -n
- cd with only a relative or absolute path
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no options
*/

int	exe_builtin(t_cmd *cmd_object, t_ms *ms)
{
	if (ft_strcmp(cmd_object->args[0], "echo") == 0)
		builtin_echo(cmd_object, STDOUT_FILENO);
	else if (ft_strcmp(cmd_object->args[0], "env") == 0)
		builtin_env(ms, 1); // fd = 1
	else if (ft_strcmp(cmd_object->args[0], "pwd") == 0)
		builtin_pwd(1); // fd = 1
	else if (ft_strcmp(cmd_object->args[0], "unset") == 0)
		builtin_unset(ms, cmd_object->args);

	// to add: exit, export, cd. Each of which still needs to be made.
	return (0);
}
