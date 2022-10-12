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

int	is_builtin(char *line)
{
	if (!ft_strncmp(line, "cd", ft_strlen(line)) || \
		!ft_strncmp(line, "echo", ft_strlen(line)) || \
		!ft_strncmp(line, "env", ft_strlen(line)) || \
		!ft_strncmp(line, "export", ft_strlen(line)) || \
		!ft_strncmp(line, "pwd", ft_strlen(line)) || \
		!ft_strncmp(line, "unset", ft_strlen(line)))
		return (TRUE);
	else
		return (FALSE);
}

// NOTE: Returns TRUE if input is a command
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

int	check_type(char *line)
{

}

t_list	*tokenizer(char	**lines, t_env **env)
{
	t_list	*token_list;


	return (token_list);
}
