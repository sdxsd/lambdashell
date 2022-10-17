#include "../includes/prototypes.h"
#include "../includes/minishell.h"
#include "../includes/structs.h"

// NOTE: INFO
// Allocates a new t_exec_element in preparation for use.
t_exec_element	*new_exec_element(void)
{
	t_exec_element	*new;

	new = malloc(sizeof(t_exec_element));
	if (!new)
		return (null_msg_err("new_exec_element()"));
	new->type = -1;
	new->next = NULL;
	new->value = NULL;
	new->line = NULL;
	return (new);
}

// NOTE: INFO
// Takes an allocated t_exec_element, and a type.
// Allocates and fills out the value of the t_exec_element.
//  +----------------------------------------+
//  | type = cmd                             |
//  | value -> +---------------------------+ |
//  |          | i_fd = STDIN_FILENO       | |
//  |          | o_fd = STDOUT_FILENO      | |
//  |          | args = ("cat" "file.txt") | |
//  |          | env = SHELL_ENV           | |
//  |          | path = "/usr/bin/cat      | |
//  |          +---------------------------+ |
//  | next ->  +----------------+            |
//  |          | t_exec_element |            |
//  |          +----------------+            |
//  +=---------------------------------------+
//
t_exec_element *assign_exec_element(t_exec_element *element, t_env **env)
{
	if (element->type == tkn_cmd)
	{
		element->value = cmd_constructor(element->line, env);
		if (!element->value)
			return (null_msg_err("assign_exec_element()"));
	}
	return (element);
}

void	dealloc_exec_list(t_exec_element *head)
{
	if (head->type == tkn_cmd)
		cmd_deallocator(head->value);
	if (head->next)
		dealloc_exec_list(head->next);
	free(head);
}

// NOTE: INFO [neads rewrite]
t_exec_element	*exec_list_generator(t_exec_element *head, t_env **env)
{
	assign_exec_element(head, env);
	if (head->next)
		return (exec_list_generator(head->next, env));
	else
		return (NULL);
}
