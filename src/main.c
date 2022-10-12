/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/28 15:59:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	clean_strings(char **dp)
{
	size_t	i;

	i = 0;
	while (dp[i])
	{
		free(dp[i]);
		i++;
	}
	free(dp);
	return (0);
}

static void	dbg_print_lines(char **lines)
{
	int	iter;

	iter = 0;
	while (lines[iter])
	{
		printf("%d: %s\n", iter, lines[iter]);
		iter++;
	}
}

int	prompt(t_ms *ms)
{
	splash();
	ms->line = readline("λ :: > ");
	line_parser(ms);
	dbg_print_lines(ms->lines);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	if (argc == 1 && argv)
	{
		//global_sig = 0;
		if (check_fd())
			return (msg_err("fd problem()", FAILURE));
		ms = ft_calloc(1, sizeof(t_ms));
		if (!ms)
			return (1);
		if (init_ms_struct(ms))
			return (msg_err("init_ms_struct()", FAILURE));
		if (init_env_struct(ms, envp))
			return (msg_err("init_env_struct()", FAILURE));
		prompt(ms);
		//clean_tokenlist(&ms->tokenlist);
		//clean_env(ms->env);
		//free (ms);
		return (0);
	}
	return (msg_err("Please do not provide any arguments.", 1));
}

/*
while (TRUE)
{
	color_orange();
	printf("λ :: > ");
	color_reset();
	ms->line = readline("");
	if (ms->line == NULL)
		break ;
	if (ms->line[0] != 0)
	{
		add_history(ms->line);
		line_parser(ms);
		printf("result: %s\n", ms->line);
	}
}
*/
