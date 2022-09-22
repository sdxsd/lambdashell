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
	element->type = type;
	if (type == tkn_cmd)
	{

	}
}

// NOTE: INFO
// This function Generates a linked list of t_exec_elements.
// This list is in essence a list of instructions and allocated
// structs for the executor to execute.
// Each element contains a type, for example, cmd or pipe_blk.
// Then a pointer to an equivalent struct, i.e. t_cmd, or t_pipe_blk.
// Finally a pointer to the next element in the list.
t_exec_element	*exec_list_generator(int *token_list)
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
	while (token_list[iter] != -1)
	{

	}
	return (head);
}

void	lnk_pipe_blk(t_pipe_blk *pipe_one, t_pipe_blk *pipe_two)
{
	int	new_pipe[2];

	pipe(new_pipe);
	pipe_one->cmd_two->o_fd = new_pipe[WRITE];
	pipe_two->cmd_one->i_fd = new_pipe[READ];
}
