/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:15:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/12 14:21:44 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
This file contains functions that are part of the input parsing section.
It analyses the input string and expands variables if applicable. Next, the
expanded string will be used for the tokenization process, where the expanded
string will be cut into pieces (i.e. words) and chained together into a 
linked list (see ms->tokens in minishell.h).
*/

#include "minishell.h"

/*
updates the line it receives on a specific location
idea is that it is run several times so it can update the line completely
it is run when another functions came across env var in the line
with the repeated ft_memcpy it iteratively builds the updated line with an
expanded var
*/
char	*line_expander_helper(char *line, int pos, t_env **env)
{
	char	*key;
	char	*val;
	char	*tmp;
	char	*res;

	key = ft_substr(line, pos + 1, ft_strpos_first_nonalpha(&line[pos + 1]));
	val = get_env_val(env, key);
	if (val == NULL)
		val = "";
	tmp = malloc((ft_strlen(line) + ft_strlen(val) + 1) * sizeof(char));
	ft_strncpy(tmp, line, pos);
	ft_strncpy(&tmp[pos], val, ft_strlen(val));
	res = ft_strjoin(tmp, &line[pos + 1 + ft_strpos_first_nonalpha(&line[pos + 1])]);
	free (key);
	free (line);
	free (tmp);
	return (res);
}

/*
Loops over string until finds env var, replaces it, continues looping over string etc.
checks for single squote (squote) presence, because everything inside them needs to be
literal without expansion
*/

char	*line_expander(char *line, t_env **env)
{
	int	squote;
	int	i;

	i = 0;
	squote = 0;
	while (line[i])
	{
		if (squote == 0)
		{
			if (line[i] == '\'')
				squote = 1;
			if (line[i] == '$')
			{
				if (!(i - 3 >= 0 && line[i - 3] == '<' && line[i - 2] == '<'))
				{
					line = line_expander_helper(line, i, env);
				}
			}
		}
		else
			if (line[i] == '\'')
				squote = 0;
		i++;
	}
	return (line);
}
