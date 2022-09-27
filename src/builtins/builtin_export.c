/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:47:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/27 23:15:22 by mikuiper      ########   odam.nl         */
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

// add to libft?
int	ft_count_char_occurrence(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
		}
		i++;
	}
	return (count);
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

// adds new var. If already exists, deletes current, then adds new var.
// possible mem leak fountain due to overwriting val. have to check.

int	builtin_export_process_var(char *key, char *val, t_ms *ms)
{
	t_env *node;

	if (!is_valid_identifier(key))
		return (1);
	// if (ft_strchr(val, '\''))
	// {
	// 	val = ft_remove_char_from_string(val, '\'');
	// }

	char *val2;
	val2 = ft_remove_char_from_string(val, '\'');
	printf("current val: %s\n", val2);
	if (env_key_exist(ms->env, key))
	{
		env_edit_var_val(ms->env, key, val2);
		return (0);
	}
	else
	{
		node = env_create_var(key, val2);
		if (!node)
			return (1); // protect?		
		env_add_var(ms, node); // protect?
	}
	return (0);
}

// todo: remove single quotes from value
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
	// if (ft_get_n_strings(cmd_object->args) == 0) // klopt dit?
	// {
	// 	builtin_export_without_args(ms, fd);
	// }
	// else
	// {
	// 	builtin_export_with_args(ms, cmd_object);
	// 	builtin_export_without_args(ms, fd); // this call has to be removed ultimately
	// }
	builtin_export_with_args(ms, cmd_object);
	builtin_export_without_args(ms, fd); // this call has to be removed ultimately
	return (0);
}


/*
// is key already exists, export should overwrite

//single quotes being fully ignored
//if double quotes present, should start and end! else, error?

// now construct value part. Remember, must be between double quotes
// note to not blindly add double quotes, because you could end up with
// double double quotes.
// add double quotes if these are absent in the value.
// If present, then do not add quotes.
//node = env_create_var(key, get_val_str(key));
//env_add_var(ms, node);
//{
// protect && free key && free key;
//}
*/