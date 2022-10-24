#include "../includes/minishell.h"
#include <stdlib.h>

int	prompt(t_ms *ms)
{
	t_exec_element *exec_list;

	ms->line = readline("λ :: > ");
	if (ft_strlen(ms->line) < 1)
		return (SUCCESS);
	parse_line(ms);
	exec_list = tokenizer(ms);
	exec_list_generator(exec_list, ms->env);
	dbg_print_exec_list(exec_list);
	executor(exec_list);
	free(ms->line);
	dealloc_exec_list(exec_list);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms *ms;

	if (argc == 1 && argv)
		while (TRUE)
			prompt(ms);
	return (SUCCESS);
}
