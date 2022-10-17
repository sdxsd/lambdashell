/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/18 13:32:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/20 22:00:21 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// NOTE: Returns TRUE if input is a builtin.
int	is_builtin(char *line)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (msg_err("is_builtin()", FAILURE));
	if (!ft_strncmp(split_line[0], "cd", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "echo", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "env", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "export", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "pwd", ft_strlen(split_line[0])) || \
		!ft_strncmp(split_line[0], "unset", ft_strlen(split_line[0])))
	{
		free_ptr_array(split_line);
		return (TRUE);
	}
	else
	{
		free_ptr_array(split_line);
		return (FALSE);
	}
}

// NOTE: Returns TRUE if input is a command.
int	is_command(char *line, t_env **env)
{
	char	**split_line;
	char	*path;

	split_line = ft_split(line, ' ');
	if (!split_line)
		return (msg_err("is_command()", FAILURE));
	path = get_path(split_line[0], env);
	free_ptr_array(split_line);
	if (!path)
		return (FALSE);
	else
	{
		free(path);
		return (TRUE);
	}
}

// NOTE: Takes line as input and returns type.
int	check_type(char *line, t_env **env)
{
	if (is_builtin(line) == TRUE)
		return (tkn_bltin);
	else if (is_command(line, env) == TRUE)
		return (tkn_cmd);
	else
		return (-1);
}

t_exec_element	*tokenizer(t_ms *shell)
{
	t_exec_element 	*exec_list;
	t_exec_element	*prev;
	t_exec_element	*curr;
	int				iter;

	iter = 1;
	exec_list = new_exec_element();
	if (!exec_list)
		return (null_msg_err("tokenizer()"));
	exec_list->type = check_type(shell->lines[0], shell->env);
	exec_list->line = shell->lines[0];
	prev = exec_list;
	while (shell->lines[iter])
	{
		curr = new_exec_element();
		if (!curr)
		{
			free_exec_list(exec_list);
			return (null_msg_err("tokenizer()"));
		}
		curr->type = check_type(shell->lines[1], shell->env);
		curr->line = shell->lines[iter];
		prev->next = curr;
		prev = curr;
		iter++;
	}
	return (exec_list);
}
