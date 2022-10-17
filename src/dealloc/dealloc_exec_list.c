#include "../../includes/minishell.h"

void	free_exec_list(t_exec_element *head)
{
	t_exec_element	*curr;
	t_exec_element	*prev;

	curr = head;
	while (curr->next)
	{
		if (curr->line != NULL)
			free(curr->line);
		if (curr->value != NULL && curr->type == tkn_cmd)
			cmd_deallocator(curr->value);
		prev = curr;
		curr = curr->next;
		free(prev);
	}
}
