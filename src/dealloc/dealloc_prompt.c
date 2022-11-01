#include "../../include/minishell.h"

void	dealloc_prompt(t_exec_element *e_list, t_shell *sh)
{
	executor(exec_list, lambda->env);
	free(lambda->line);
	free_ptr_array(lambda->lines);
	dealloc_exec_list(exec_list);
}
