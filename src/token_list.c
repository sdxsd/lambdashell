#include "../includes/prototypes.h"
#include "../includes/minishell.h"
#include "../includes/structs.h"

t_exec_element	*new_token_element(void)
{
	t_exec_element	*new;

	new = malloc(sizeof(t_exec_element));
	if (!new)
	{
		msg_err("new_token_element()", FAILURE);
		return (NULL);
	}
	new->type = -1;
	new->next = NULL;
	new->value = NULL;
	return (new);
}

t_exec_element *assign_token_element(t_exec_element *element, int type)
{
	element->type = type;
	if (type == tkn_cmd)
	{

	}
}

t_exec_element	*token_list_generator(int *token_list)
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
