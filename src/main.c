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


int	prompt(t_ms *ms)
{
	t_line_blk	*lblk;
	t_cmd		*cmd;

	splash();
	//ms->line = readline("λ :: > ");
	ms->line = ft_strdup("ls | wc");
	//printf("Minishell is currently parsing:\n%s\n\n", ms->line);
	line_parser(ms);
	lblk = line_blk_array_generator(ms->lines, 1);
	(void)lblk;
	cmd = cmd_constructor(lblk->val[0], ms->env);
	(void)cmd;
	cmd->args = ft_split("USER=mik'uipersss TERM=c'o''d'am", ' ');
	//printf("%s", cmd->args[3]); // segfault @ 3
	builtin_export(ms, cmd, 1);
	//clean_strings(cmd->env);
	
	clean_strings(cmd->args);
	free(cmd);
	clean_strings(ms->lines);
	//free(ms->line);
	//clean_strings(ms->lines);
	//free (cmd);
	
	//execute_command(cmd);
	//printf("cmd->args: %s\n", ms->lines[1]);
	/*
	t_cmd	*cmd;
	ms->line = ft_strdup("Hi, the shell you are using is < | $SHELL");
	line_parser(ms);
	(void)cmd;
	cmd = cmd_constructor("nano", ms->env);
	if (!cmd)
		return (FAILURE);
	execute_command(cmd);
	*/
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
