/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_start.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:05:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/06 20:57:20 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_token_tag
{
	tkn_pipe,
	tkn_str,
	tkn_heredoc,
	tkn_read,
	tkn_write,
	tkn_append
}				t_token_tag;

typedef struct s_token
{
	t_token_tag	tag;
	char		*txt;
}				t_token;

/*
updates the line it receives on a specific location
idea is that it is run several times so it can update the line completely
it is run when another functions came across env var in the line
with the repeated ft_memcpy it iteratively builds the updated line with an
expanded var
*/
char	*tkn_expander_helper(char *line, int pos, t_env **env)
{
	char	*new_line;
	char	*key;
	char	*val;

	key = ft_substr(line, pos + 1, ft_strpos_charset(&line[pos + 1], \
		" \t\n\'\"$|*<>"));
	val = get_env_val(env, key);
	if (!val)
		val = '\0';
	new_line = malloc((ft_strlen(line) + ft_strlen(val) + 1) * sizeof(char));
	ft_memcpy(new_line, line, pos);
	ft_memcpy(&new_line[pos], val, ft_strlen(val));
	ft_strcpy(&new_line[pos + ft_strlen(val)], &line[pos + 1 + \
	ft_strpos_charset(&line[pos + 1], " \t\n\'\"$|*<>")]);
	free(key);
	free(line);
	return (new_line);
}

/*
Loops over string until finds env var, replaces it, continues looping over string etc.
checks for single squote (squote) presence, because everything inside them needs to be
literal without expansion
*/

char	*tkn_expander(char *line, t_env **env)
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
					line = tkn_expander_helper(line, i, env);
			}	
		}
		else
			if (line[i] == '\'')
				squote = 0;
		i++;
	}
	return (line);
}

void	line_parser(t_ms *ms)
{
	ms->line = tkn_expander(ms->line, ms->env);
	printf("%s\n", ms->line);
}


int	minishell_start(t_ms *ms)
{
	// ms->line = ft_strdup("hey\"$HOME$SHLVL$COLORTERM\"");
	// line_parser(ms);
	while (1)
	{
		ms->line = readline("\033[;32m$> \033[0;0m\2");
		if (ms->line == NULL)
			break ;
		if (ms->line[0] != 0)
		{
			add_history(ms->line);
			line_parser(ms);
		}
	}
	return (0);
}