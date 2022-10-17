#include "../../includes/minishell.h"

void	dbg_print_lines(char **lines)
{
	int	iter;

	iter = 0;
	while (lines[iter])
	{
		printf("%d: %s\n", iter, lines[iter]);
		iter++;
	}
}

/* NOTE: To be called after running the tokenizer() function. */
void	dbg_print_exec_list(t_exec_element *head)
{
	if (head->type == tkn_cmd)
		printf("Type: [cmd]\n");
	else if (head->type == tkn_bltin)
		printf("Type: [builtin]\n");
	printf("Line: %s\n", head->line);
	printf("Value: %p\n", head->value);
	printf("next: %p\n\n", head->next);
	if (head->next)
		dbg_print_exec_list(head->next);
}
