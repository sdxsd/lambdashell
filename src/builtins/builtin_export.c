/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:47:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/22 21:29:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_key_string(char *s)
{
	char	*key;
	int		i;

	i = 0;
	if (!(key = malloc(sizeof(char) * (ft_print_until_char(s, '=') + 1))))
	{
		return (NULL);
	}
	while (s[i] != '=' && s[i])
	{
		key[i] = s[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_val_string(char *s)
{
	char	*key;
	int		key_len;

	key = get_key_string(s);
	key_len = ft_strlen(key);
	if (!ft_strchr(s, '='))
	{
		free(key);
		key = NULL;
		return (NULL);
	}
	free(key);
	key = NULL;
	return (&s[key_len + 1]);
}

void	builtin_export_print(char **env_arrays, int fd)
{
	int		i;
	char	*tmp;

	if (!env_arrays)
		return ;
	i = 0;
	while (env_arrays[i])
	{
		tmp = get_key_string(env_arrays[i]);
		if (ft_strncmp("_", tmp, ft_strlen(env_arrays[i])))
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp, fd);
			if (get_val_string(env_arrays[i]))
			{
				ft_putstr_fd("=\"", fd);
				ft_putstr_fd(get_val_string(env_arrays[i]), fd);
				ft_putstr_fd("\"", fd);
			}
			ft_putstr_fd("\n", fd);
		}
		free(tmp);
		tmp = NULL;
		i++;
	}
}

int	builtin_export_without_args(t_ms *ms, int fd)
{
	char	**env_arrays;

	env_arrays = env_entries_to_arrays(ms->env);
	ft_sort_array_strings(env_arrays);
	builtin_export_print(env_arrays, fd);
	ft_free_array_strings(env_arrays);
	return (0);
}

int	builtin_export(t_ms *ms, t_cmd *cmd_object, int fd)
{
	if (ft_get_n_strings(cmd_object->args) == 1)
	{
		builtin_export_without_args(ms, fd);
	}
	else
	{
		// TODO!
		printf("builtin_exports, else, TODO!\n");
	}
	return (0);
}
