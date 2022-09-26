/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:47:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/26 22:45:31 by mikuiper      ########   odam.nl         */
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

int	is_valid_identifier(char *s)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(s[0]))
	{
		return (0);
	}
	while (s[i])
	{
		if (!ft_isalpha(s[i] && !ft_isdigit(s[i] && s[i] != '_')))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	builtin_export_with_args(t_ms *ms, t_cmd *cmd_object)
{
	size_t	i;
	char	*key;
	t_env	*node;

	i = 1;
	while (cmd_object->args[i])
	{
		// check if equals present
		// if not present, simple
		if (!ft_strchr(cmd_object->args[i], '='))
		{
			//printf("= not found\n");
			key = ft_strdup(cmd_object->args[i]);
			//if (!key)
			// todo protect	
		}
		// if is present, then get corresponding key
		else
		{
			//printf("= found\n");
			key = get_key_string(key);
			//if (!key)
			// todo protect
		}
		//printf("key: %s\n", key);
		if (!is_valid_identifier(key))
		{
			//printf("key is not valid identifier\n");
			return ;
			// cleanup
			// trigger error
		}
		//printf("key is valid identifier! key: %s}\n", key);
		// now construct value part. Remember, must be between double quotes
		// note to not blindly add double quotes, because you could end up with
		// double double quotes.
		// add double quotes if there are absent in the value.
		// If present, then do not add quotes.
		node = env_create_var(key, get_val_string(key));
		(void)ms;
		(void)node;
		//env_add_var(ms, node);
		//{
		// protect && free key && free key;
		//}
		free(key);
		i++;
	}
	//debug_print_env(ms);
}

int	builtin_export(t_ms *ms, t_cmd *cmd_object, int fd)
{
	/*
	if (ft_get_n_strings(cmd_object->args) == 1)
	{
		builtin_export_without_args(ms, fd);
	}
	else
	{
		builtin_export_with_args(ms, cmd_object);
		//builtin_export_without_args(ms, fd);
	}
	*/
	//builtin_export_without_args(ms, fd); // IS AL AF!
	//builtin_export_with_args(ms, cmd_object); // NOG NIET AF + SEGFAULT
	(void)ms;
	(void)cmd_object;
	(void)fd;
	return (0);
}
