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
	{
		msg_err("new_exec_element()", FAILURE);
		return (NULL);
	}
	new->type = -1;
	new->next = NULL;
	new->value = NULL;
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
t_exec_element *assign_exec_element(t_exec_element *element, int type, t_env **env, char **input)
{
	if (element->type == tkn_cmd)
	{
		element->value = cmd_constructor(*input, env);
		if (!element->value)
		{
			msg_err("assign_exec_element()", FAILURE);
			return (NULL);
		}
	}
	else if (element->type == tkn_pipe)
	{
		pipe_blk_alloc(input[0], input[1], STDIN_FILENO, STDOUT_FILENO, env);
		if (!element->value)
		{
			msg_err("assign_exec_element()", FAILURE);
			return (NULL);
		}
	}
	return (element);
}

void	dealloc_exec_list(t_exec_element *head)
{
	if (head->type == tkn_cmd)
		cmd_deallocator(head->value);
	if (head->type == tkn_pipe)
		pipe_blk_dealloc(head->value);
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
t_exec_element	*exec_list_generator(t_line_blk *line_blks, int n_blocks, t_env **env)
{
	t_exec_element	*head;
	t_exec_element	*curr_element;
	int				iter;

	iter = 0;
	head = new_exec_element();
	if (!head)
	{
		msg_err("token_list_generator()", FAILURE);
		return (NULL);
	}
	curr_element = head;
	while (iter < n_blocks)
	{
		assign_exec_element(curr_element, line_blks->type, env, line_blks->val);
		iter++;
		line_blks++;
		curr_element->next = new_exec_element();
		if (!curr_element->next)
		{
			msg_err("exec_list_generator()", FAILURE);
			dealloc_exec_list(head);
		}
		curr_element = curr_element->next;
	}
	return (head);
}
