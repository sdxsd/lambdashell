/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/07 23:19:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/09 15:48:12 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_parser(t_ms *ms)
{
	ms->line = line_expander(ms->line, ms->env);
	printf("\n%s\n", ms->line);
}

int	prompt(t_ms *ms)
{

	ms->line = ft_strdup("$HOME@@@$HOME");
	line_parser(ms);
	// while (1)
	// {
	// 	ms->line = readline("\033[;32m$> \033[0;0m\2");
	// 	if (ms->line == NULL)
	// 		break ;
	// 	if (ms->line[0] != 0)
	// 	{
	// 		add_history(ms->line);
	// 		line_parser(ms);
	// 	}
	// }
	return (0);
}

/*
TODO:
What if env key not exists? now $HOM will give segfault (vs $HOME)
Fix that $HOMEF with return $HOME value
*/