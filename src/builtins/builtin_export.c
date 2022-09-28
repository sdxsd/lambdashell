/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:47:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/28 16:21:12 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_key_str(char *s)
{
	char	*key;
	int		i;

	i = 0;
	if (!(key = malloc(sizeof(char) * (ft_print_until_char(s, '=') + 1))))
		return (NULL);
	while (s[i] != '=' && s[i])
	{
		key[i] = s[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_val_str(char *s)
{
	char	*key;
	int		key_len;

	key = get_key_str(s);
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
		tmp = get_key_str(env_arrays[i]);
		if (ft_strncmp("_", tmp, ft_strlen(env_arrays[i])))
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(tmp, fd);
			if (get_val_str(env_arrays[i]))
			{
				ft_putstr_fd("=\"", fd);
				ft_putstr_fd(get_val_str(env_arrays[i]), fd);
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
	i++;
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	*ft_remove_char_from_string(char *val, char c)
{
	char	*newval;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	newval = malloc(ft_strlen(val) - ft_count_char_occurrence(val, c));
	if (!newval)
		return (NULL);
	while (val[i])
	{
		if (val[i] == c)
		{
			i++;
			continue;
		}
		newval[j] = val[i];
		j++;
		i++;
	}
	newval[j] = '\0';
	return (newval);
}

int	builtin_export_var_has_squotes(char *key, char *val, t_ms *ms)
{
	t_env	*node;
	char	*val_new;

	val_new = ft_remove_char_from_string(val, '\'');
	if (env_key_exist(ms->env, key))
	{
		env_edit_var_val(ms->env, key, val_new);
		free (val_new);
		return (0);
	}
	else
	{
		node = env_create_var(key, val_new);
		if (!node)
		{
			free (val_new);
			return (1);
		}
		env_add_var(ms, node);
	}
	return (0);
}

int	builtin_export_var_no_squotes(char *key, char *val, t_ms *ms)
{
	t_env	*node;

	if (env_key_exist(ms->env, key))
	{
		env_edit_var_val(ms->env, key, val);
		return (0);
	}
	else
	{
		node = env_create_var(key, val);
		if (!node)
			return (1);
		env_add_var(ms, node);
	}
	return (0);
}

int	builtin_export_process_var(char *key, char *val, t_ms *ms)
{
	if (!is_valid_identifier(key))
		return (1);
	if (ft_strchr(val, '\''))
	{
		if (builtin_export_var_has_squotes(key, val, ms))
			return (1);
	}
	else
	{
		if (builtin_export_var_no_squotes(key, val, ms))
			return (1);
	}
	return (0);
}

int	builtin_export_with_args(t_ms *ms, t_cmd *cmd_object)
{
	size_t	i;
	char	*key;

	i = 0;
	while (cmd_object->args[i])
	{
		if (!ft_strchr(cmd_object->args[i], '='))
		{
			key = ft_strdup(cmd_object->args[i]);
			if (!key)
				return (1);
		}
		else
		{
			key = get_key_str(cmd_object->args[i]);
			if (!key)
				return (1);
		}
		if (builtin_export_process_var(key, get_val_str(cmd_object->args[i]), ms))
			return (1);
		free(key);
		i++;
	}
	return (0);
}

int	builtin_export(t_ms *ms, t_cmd *cmd_object, int fd)
{
	// check whether this needs to be == 0 or 1
	if (ft_get_n_strings(cmd_object->args) == 0)
	{
		builtin_export_without_args(ms, fd);
	}
	else
	{
		builtin_export_with_args(ms, cmd_object);
	}
	return (0);
}
