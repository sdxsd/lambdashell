/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/31 13:05:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/08/31 13:05:48 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_prompt(t_ms *ms)
{
	while (1)
	{
		ms->input_line = readline(">");
		if (ms->input_line)
		{
			parse_input(ms, ms->input_line);
		}
	}
	(void)ms;
}
