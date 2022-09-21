/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:15:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/19 23:32:03 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains functions that are part of the input parsing section.
It analyses the input string and expands variables if applicable. Next, the
expanded string will be used for the tokenization process, where the expanded
string will be cut into pieces (i.e. words) and chained together into a 
linked list (see ms->tokenlist in minishell.h).
*/

#include "../includes/minishell.h"

/*
line_insert_var() pdates the line it receives on a specific location
idea is that it is run several times so it can update the line completely
it is run when another functions came across env var in the line
with the repeated ft_memcpy it iteratively builds the updated line with an
expanded var
*/
char	*line_insert_var(char *line, int pos, t_env **env)
{
	char	*key;
	char	*val;
	char	*newline;
	key = ft_substr(line, pos + 1, ft_strpos_first_nonalpha(&line[pos + 1]));
	val = env_get_val(env, key);
	if (val == NULL)
		val = "";
	newline = malloc((ft_strlen(line) + ft_strlen(val) + 1) * sizeof(char));
	ft_memcpy(newline, line, pos);
	ft_memcpy(&newline[pos], val, ft_strlen(val));
	ft_strcpy(&newline[pos + ft_strlen(val)], &line[pos + 1 + \
	ft_strpos_first_nonalpha(&line[pos + 1])]);
	free (key);
	free (line);
	return (newline);
}

int	line_dollar_presence(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && line[i + 1])
		{
			i++;
			while (line[i] && line[i] != '\'')
			{
				i++;
			}
		}
		else if (line[i] == '$')
		{
			return (1);
		}
		if (line[i])
		{
			i++;
		}
	}
	return (0);
}

char	*line_expander(char *line, t_env **env)
{
	size_t	i;
	size_t	n;

	n = 0;
	while (line && line_dollar_presence(line))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '$')
			{
				line = line_insert_var(line, i, env);
				break ;
			}
			if (line[i])
				i++;
		}
		n++;
	}
	if (n == 0)
		return (ft_strdup(line));
	return (line);
}
