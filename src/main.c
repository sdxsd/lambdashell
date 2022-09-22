/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/09/20 21:21:15 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*              @@@@@@@                    Ommmm.  Ommmm. */
/*             @@     @@                   Blessed be UNIX. */
/*            @@  ^ ^  @@                  Blessed be the UNIX keepers. */
/*            @@   "   @@                  May they look kindly upon */
/*             @\  O  /@                   humble petitioners. */
/*               '---' */
/*            ____| |____                  Ommmm.  Ommmm. */
/*           /   |   |   \                 May the poor receive more CPU time. */
/*         __| |  \ /  | |__               May Magic crash less often. */
/*        /  | |   *   | |  \              May Mercury receive more virtual */
/*       /   / |       | \   \             memory space for swapping. */
/*      /   / /|==%====|\ \   \ */
/*     / _O/ / /   _   \ \ \O_ \           Ommmm.  Ommmm. */
/*    /  =,_/ /   / \   \ \_,=  \          Blessed be UNIX. */
/*   /       /   // \\   \       \         Blessed be the UNIX keepers. */
/*  /        \__//   \\__/        \        May they act swiftly and surely */
/* /                               \       on these humble requests. */
/* ################################# */

int	prompt(t_ms *ms)
{
	t_line_blk	*lblk;
	t_pipe_blk	*pipe_blk_test;

	splash();
	ms->line = readline("λ :: > ");
	printf("Minishell is currently parsing:\n%s\n\n", ms->line);
	line_parser(ms);
	lblk = line_blk_array_generator(ms->lines, 2);
	pipe_blk_test = pipe_blk_alloc(lblk->val[0], lblk->val[1], STDIN_FILENO, STDOUT_FILENO, ms->env);
	if (!pipe_blk_test)
		return FAILURE;
	execute_pipe_blk(pipe_blk_test);
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
		while (prompt(ms))
		{

		}
		//free (ms->line);
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
