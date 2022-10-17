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
// Example, if the type is cmd, a t_cmd struct is allocated
// using input[0] and t_env **env.
// If the type is a pipe block, then
// input[0] and input[1] are sent to pipe_blk_alloc, along with t_env **env.
// Final output in memory might look like so:
//         EXEC_ELEMENT (here "->" is used to indicate pointer)
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

// NOTE: INFO
// This function Generates a linked list of t_exec_elements.
// This list is in essence a list of instructions and allocated
// structs for the executor to execute.
// Each element contains a type, for example, cmd or pipe_blk.
// Then a pointer to an equivalent struct, i.e. t_cmd, or t_pipe_blk.
// Finally a pointer to the next element in the list.
t_exec_element	*exec_list_generator(t_exec_element *head, t_env **env)
{
	t_exec_element	*curr_element;

	curr_element = head;
	while (curr_element->next)
	{
		assign_exec_element(curr_element, env);
		curr_element = curr_element->next;
	}
	return (head);
}
