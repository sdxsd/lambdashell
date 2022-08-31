/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   old_env_tools.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 15:03:21 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 21:03:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	substring_start(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && (i != ft_strlen(s2)))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ms_strjoin(char *s1, char *s2, char c)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i] = c;
	i++;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

int	env_write_entry(t_ms *ms, int pos, char *entry)
{
	ms->env[pos] = ft_strdup(entry);
	if (!ms->env[pos])
		return (1);
	return (0);
}

int	env_find_key(t_ms *ms, char *key)
{
	int		i;
	char	*key_tmp;

	i = 0;
	key_tmp = ms_strjoin(key, "", '=');
	if (!key_tmp)
		return (-1);
	while (ms->env[i])
	{
		if (substring_start(ms->env[i], key_tmp))
		{
			free (key_tmp);
			return (i);
		}
		i++;
	}
	free (key_tmp);
	return (-1);
}

int	env_add_entry(t_ms *ms, char *key, char *value)
{
	int		i;
	char	*entry;
	
	i = env_find_key(ms, key);
	entry = ms_strjoin(key, value, '=');
	if (entry == NULL)
		return (1);
	if (i != -1)
	{
		free (ms->env[i]);
		env_write_entry(ms, i, entry);
	}
	else
	{
		i = 0;
		while (ms->env[i])
			i++;
		env_write_entry(ms, i, entry);
		i++;
		//ms->env[i] = ft_calloc(1, (sizeof(char *)));
	}
	free (entry);
	return (0);
}

char *get_env_val(t_ms *ms, char *key)
{
	char	*entry;
	char	**entry_split;
	char	*val;

	if (env_find_key(ms, key) != -1)
	{
		entry = ft_strdup(ms->env[env_find_key(ms, key)]);
		if (!entry)
			return (NULL);
		entry_split = ft_split(entry, '=');
		if (!entry_split)
			return (NULL);
		val = ft_strdup(entry_split[1]);
		if (!val)
		{
			free (entry);
			clean_dp(entry_split);
			return (NULL);
		}
		clean_dp(entry_split);
		free (entry);
		return (val);
	}
	return (NULL);
}

int	str_only_nbrs(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' && s[i + 1])
		i++;
	else if (!ft_isdigit(s[i]))
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	env_shlvl(t_ms *ms)
{
	int		i_shlvl;
	char	*s_shlvl;

	if (env_find_key(ms, "SHLVL") != -1)
	{
		s_shlvl = get_env_val(ms, "SHLVL");
		if (!s_shlvl)
			return (-1);
		if (!str_only_nbrs(s_shlvl))
		{
			free (s_shlvl);
			return (-1);
		}
		i_shlvl = ft_atoi(s_shlvl);
		free (s_shlvl);
		return (i_shlvl);
	}
	return (1);
}
*/***************************************** */

#include "minishell.h"

/*
int	substring_start(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && (i != ft_strlen(s2)))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ms_strjoin(char *s1, char *s2, char c)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i] = c;
	i++;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

int	env_write_entry(t_ms *ms, int pos, char *entry)
{
	ms->env[pos] = ft_strdup(entry);
	if (!ms->env[pos])
		return (1);
	return (0);
}

int	env_find_key(t_ms *ms, char *key)
{
	int		i;
	char	*key_tmp;

	i = 0;
	key_tmp = ms_strjoin(key, "", '=');
	if (!key_tmp)
		return (-1);
	while (ms->env[i])
	{
		if (substring_start(ms->env[i], key_tmp))
		{
			free (key_tmp);
			return (i);
		}
		i++;
	}
	free (key_tmp);
	return (-1);
}

int	env_add_entry(t_ms *ms, char *key, char *value)
{
	int		i;
	char	*entry;
	
	i = env_find_key(ms, key);
	entry = ms_strjoin(key, value, '=');
	if (entry == NULL)
		return (1);
	if (i != -1)
	{
		free (ms->env[i]);
		env_write_entry(ms, i, entry);
	}
	else
	{
		i = 0;
		while (ms->env[i])
			i++;
		env_write_entry(ms, i, entry);
		i++;
		//ms->env[i] = ft_calloc(1, (sizeof(char *)));
	}
	free (entry);
	return (0);
}

char *get_env_val(t_ms *ms, char *key)
{
	char	*entry;
	char	**entry_split;
	char	*val;

	if (env_find_key(ms, key) != -1)
	{
		entry = ft_strdup(ms->env[env_find_key(ms, key)]);
		if (!entry)
			return (NULL);
		entry_split = ft_split(entry, '=');
		if (!entry_split)
			return (NULL);
		val = ft_strdup(entry_split[1]);
		if (!val)
		{
			free (entry);
			clean_dp(entry_split);
			return (NULL);
		}
		clean_dp(entry_split);
		free (entry);
		return (val);
	}
	return (NULL);
}

int	str_only_nbrs(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' && s[i + 1])
		i++;
	else if (!ft_isdigit(s[i]))
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	env_shlvl(t_ms *ms)
{
	int		i_shlvl;
	char	*s_shlvl;

	if (env_find_key(ms, "SHLVL") != -1)
	{
		s_shlvl = get_env_val(ms, "SHLVL");
		if (!s_shlvl)
			return (-1);
		if (!str_only_nbrs(s_shlvl))
		{
			free (s_shlvl);
			return (-1);
		}
		i_shlvl = ft_atoi(s_shlvl);
		free (s_shlvl);
		return (i_shlvl);
	}
	return (1);
}
*/