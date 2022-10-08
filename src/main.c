/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/19 21:20:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/10/08 20:35:50 by mikuiper      ########   odam.nl         */
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

int	prompt(t_ms *ms)
{
	t_line_blk	*lblk;
	t_exec_element *exec_list;
	t_pipe_blk	*pipe_blk_test;

	splash();
	//ms->line = readline("λ :: > ");
	ms->line = ft_strdup("cd | cd");
	//printf("Minishell is currently parsing:\n%s\n\n", ms->line);
	line_parser(ms);
	lblk = line_blk_array_generator(ms->lines, 2);
	exec_list = exec_list_generator(lblk, 2, ms->env);
	pipe_blk_test = exec_list->value;
	//execute_pipe_blk(pipe_blk_test);
	(void)pipe_blk_test;
	char **fake_cmd1;
	fake_cmd1 = ft_split("cd /home/mkuipers/Desktop", ' ');
	builtin_cd2(fake_cmd1, ms);
	printf("processed builtin_cd2()\n");
	char s[100];
	printf("%s\n", getcwd(s, 100));
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
